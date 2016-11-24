set(SRCS
	gtest.cc
	gtest_main.cc 
	gtest-all.cc 
	gtest-death-test.cc 
	gtest-filepath.cc 
	gtest-internal-inl.h
	gtest-port.cc
	gtest-printers.cc 
	gtest-test-part.cc 
	gtest-typed-test.cc
    )

add_library(gtest ${SRCS})


