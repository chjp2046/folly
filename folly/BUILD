cc_library(
	name = "follybase",
	srcs = [
		'Conv.cpp',
		'Demangle.cpp',
		'EscapeTables.cpp',
		'Format.cpp',
		'FormatTables.cpp',
		'Malloc.cpp',
		'Range.cpp',
		'String.cpp',
		'Unicode.cpp',
		#'detail/Clock.cpp',
		'detail/MallocImpl.cpp',
		#'detail/FunctionalExcept.cpp',
        'StringBase.cpp'
	],
	deps = [
		'//thirdparty/glog:glog',
		'//thirdparty/gflags:gflags',
		'//thirdparty/openssl:ssl',
	    '//thirdparty/openssl:crypto',
		'//thirdparty/double-conversion:double-conversion',
		'//thirdparty/libevent:event',
		'//thirdparty/snappy:snappy',
		'//boost:boost_thread',
		'//boost:boost_filesystem',
		'//boost:boost_system',
		'//boost:boost_regex',
        '//boost:boost_context',
		'//thirdparty/lz4:lz4',
		'#lzma',
		'#z',
		'#pthread'
	],
	extra_cppflags = [
		'-std=gnu++0x',
		'-DHAVE_CONFIG_H'
	],
	warning = 'no',
    link_all_symbols=1
)

cc_binary(
    name = 'generate_fingerprint_tables',
    srcs = [
        'build/GenerateFingerprintTables.cpp'
    ],
    deps = [
        ':follybase'
    ],
	extra_cppflags = [
		'-std=gnu++0x'
	],
	warning = 'no'
)



cc_library(
	name = "folly",
	srcs = [
		'Bits.cpp',
		'detail/CacheLocality.cpp',
		'dynamic.cpp',
		'File.cpp',
		'FileUtil.cpp',
		'FingerprintTables.cpp',
		'futures/detail/ThreadWheelTimekeeper.cpp',
		'futures/Future.cpp',
		'futures/InlineExecutor.cpp',
		'futures/ManualExecutor.cpp',
		'futures/QueuedImmediateExecutor.cpp',
		'detail/Futex.cpp',
		'GroupVarint.cpp',
		'GroupVarintTables.cpp',
		'IPAddress.cpp',
		'IPAddressV4.cpp',
		'IPAddressV6.cpp',
		'LifoSem.cpp',
		'io/Compression.cpp',
		'io/IOBuf.cpp',
		'io/IOBufQueue.cpp',
		'io/RecordIO.cpp',
		'io/ShutdownSocketSet.cpp',
		'io/async/AsyncTimeout.cpp',
		'io/async/AsyncUDPSocket.cpp',
		'io/async/AsyncServerSocket.cpp',
		'io/async/AsyncSignalHandler.cpp',
		'io/async/AsyncSocket.cpp',
		'io/async/AsyncSSLSocket.cpp',
		'io/async/EventBase.cpp',
		'io/async/EventBaseManager.cpp',
		'io/async/EventHandler.cpp',
		'io/async/SSLContext.cpp',
		'io/async/HHWheelTimer.cpp',
		'io/async/test/TimeUtil.cpp',
		'json.cpp',
		'detail/MemoryIdler.cpp',
		'MacAddress.cpp',
		'MemoryMapping.cpp',
		'Random.cpp',
		'SafeAssert.cpp',
		'SocketAddress.cpp',
		'SpookyHashV1.cpp',
		'SpookyHashV2.cpp',
		'stats/Instantiations.cpp',
		'Subprocess.cpp',
		'ThreadCachedArena.cpp',
		'TimeoutQueue.cpp',
		'Uri.cpp',
		'Version.cpp',
		'experimental/fibers/Baton.cpp',
		'experimental/fibers/Fiber.cpp',
		'experimental/fibers/FiberManager.cpp',
		'experimental/fibers/FiberManagerMap.cpp',
		'experimental/fibers/TimeoutController.cpp',
		'experimental/FunctionScheduler.cpp',
		'experimental/io/FsUtil.cpp',
		'experimental/JSONSchema.cpp',
		'experimental/Select64.cpp',
		'experimental/SharedMutex.cpp',
		'Singleton.cpp',
		'experimental/TestUtil.cpp',
		'wangle/acceptor/Acceptor.cpp',
		'wangle/acceptor/ConnectionManager.cpp',
		'wangle/acceptor/LoadShedConfiguration.cpp',
		'wangle/acceptor/ManagedConnection.cpp',
		'wangle/acceptor/SocketOptions.cpp',
		'wangle/acceptor/TransportInfo.cpp',
		'wangle/bootstrap/ServerBootstrap.cpp',
		'wangle/concurrent/CPUThreadPoolExecutor.cpp',
		'wangle/concurrent/Codel.cpp',
		'wangle/concurrent/IOThreadPoolExecutor.cpp',
		'wangle/concurrent/GlobalExecutor.cpp',
		'wangle/concurrent/ThreadPoolExecutor.cpp',
		'wangle/ssl/PasswordInFile.cpp',
		'wangle/ssl/SSLContextManager.cpp',
		'wangle/ssl/SSLSessionCacheManager.cpp',
		'wangle/ssl/SSLUtil.cpp',
		'wangle/ssl/TLSTicketKeyManager.cpp',
		'experimental/io/HugePages.cpp'
	],
	deps = [
		':follybase'
	],
	extra_cppflags = [
		'-std=gnu++0x',
		'-DHAVE_CONFIG_H'
	],
	warning = 'no'
)

cc_library(
	name = "follybenchmark",
	srcs = [
		'Benchmark.cpp'
	],
	deps = [
		':folly'
	],
	extra_cppflags = [
		'-std=gnu++0x'
	],
	export_incs = '.',
	warning = 'no'
)

