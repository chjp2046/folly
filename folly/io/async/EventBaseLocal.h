/*
 * Copyright 2015 Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#if !defined(ANDROID) && !defined(__ANDROID__) && !defined(__APPLE__)

#include <boost/noncopyable.hpp>
#include <folly/Synchronized.h>
#include <folly/io/async/EventBase.h>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <unordered_set>

namespace folly {

namespace detail {

class EventBaseLocalBase : boost::noncopyable {
 public:
  EventBaseLocalBase() {}
  virtual ~EventBaseLocalBase();
  void erase(EventBase& evb);
  void onEventBaseDestruction(EventBase& evb);

 protected:
  void setVoid(EventBase& evb, std::shared_ptr<void>&& ptr);
  void setVoidUnlocked(EventBase& evb, std::shared_ptr<void>&& ptr);
  void* getVoid(EventBase& evb);

  folly::Synchronized<std::unordered_set<EventBase*>> eventBases_;
  static std::atomic<uint64_t> keyCounter_;
  uint64_t key_{keyCounter_++};
};

}

/**
 * A storage abstraction for data that should be tied to an EventBase.
 *
 *   struct Foo { Foo(int a, int b); };
 *   EventBaseLocal<Foo> myFoo;
 *   ...
 *   EventBase evb;
 *   myFoo.set(evb, new Foo(1, 2));
 *   myFoo.set(evb, 1, 2);
 *   Foo* foo = myFoo.get(evb);
 *   myFoo.erase(evb);
 *   Foo& foo = myFoo.getOrCreate(evb, 1, 2); // ctor
 *   Foo& foo = myFoo.getOrCreate(evb, 1, 2); // no ctor
 *   myFoo.erase(evb);
 *   Foo& foo = myFoo.getOrCreateFn(evb, [] () { return new Foo(3, 4); })
 *
 * The objects will be deleted when the EventBaseLocal or the EventBase is
 * destructed (whichever comes first).  All methods are thread-safe.
 *
 * The user is responsible for throwing away invalid references/ptrs returned
 * by the get() method after set/erase is called.  If shared ownership is
 * needed, use a EventBaseLocal<shared_ptr<...>>.
 */
template<typename T>
class EventBaseLocal : public detail::EventBaseLocalBase {
 public:
  EventBaseLocal(): EventBaseLocalBase() {}

  T* get(EventBase& evb) {
    return static_cast<T*>(getVoid(evb));
  }

  void emplace(EventBase& evb, T* ptr) {
    std::shared_ptr<T> smartPtr(ptr);
    setVoid(evb, std::move(smartPtr));
  }

  template<typename... Args>
  void emplace(EventBase& evb, Args... args) {
    auto smartPtr = std::make_shared<T>(args...);
    setVoid(evb, smartPtr);
  }

  template<typename... Args>
  T& getOrCreate(EventBase& evb, Args... args) {
    std::lock_guard<std::mutex> lg(evb.localStorageMutex_);

    auto it2 = evb.localStorage_.find(key_);
    if (LIKELY(it2 != evb.localStorage_.end())) {
      return *static_cast<T*>(it2->second.get());
    } else {
      auto smartPtr = std::make_shared<T>(args...);
      auto ptr = smartPtr.get();
      setVoidUnlocked(evb, std::move(smartPtr));
      return *ptr;
    }
  }

  template <typename Func>
  T& getOrCreateFn(EventBase& evb, Func& fn) {
    // If this looks like it's copy/pasted from above, that's because it is.
    // gcc has a bug (fixed in 4.9) that doesn't allow capturing variadic
    // params in a lambda.
    std::lock_guard<std::mutex> lg(evb.localStorageMutex_);

    auto it2 = evb.localStorage_.find(key_);
    if (LIKELY(it2 != evb.localStorage_.end())) {
      return *static_cast<T*>(it2->second.get());
    } else {
      std::shared_ptr<T> smartPtr(fn());
      auto ptr = smartPtr.get();
      setVoidUnlocked(evb, std::move(smartPtr));
      return *ptr;
    }
  }
};


}

#endif // !__ANDROID__ && !ANDROID && !__APPLE__
