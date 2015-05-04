cmake_minimum_required(VERSION 2.6)
project(ElmoSeram)

set(CMAKE_CXX_FLAGS "-std=c++0x -O2 -Wall ${CMAKE_CXX_FLAGS}")

set(ELMOSERAM_BIN	elmoseram)

set(MYSQL_LIBS	-lmysqlcppconn)

set(ELMOSERAM_SUBDIRS
		src 
		src/Connection/Server 
		src/Connection/Client 
		src/Manager 
		src/Utilities 
		src/Database)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

foreach(SRC_DIR ${ELMOSERAM_SUBDIRS})
	file(GLOB filelist "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/*.cpp")
	foreach(filename ${filelist})
    	set(SRCS ${SRCS} ${filename})
	endforeach(filename)
endforeach(SRC_DIR)

foreach(SRC_DIR ${ELMOSERAM_SUBDIRS})
	file(GLOB filelist "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/*.h")
	foreach(filename ${filelist})
    	set(INCS ${INCS} ${filename})
	endforeach(filename)
endforeach(SRC_DIR)

find_package(Boost COMPONENTS thread system REQUIRED)
find_package(OpenSSL REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR} ${ELMOSERAM_SUBDIRS})
add_executable(${ELMOSERAM_BIN} ${SRCS} ${INCS})
target_link_libraries(${ELMOSERAM_BIN} ${Boost_LIBRARIES} ${OPENSSL_CRYPTO_LIBRARIES} ${MYSQL_LIBS})

add_custom_target(run
		COMMAND ./${ELMOSERAM_BIN}
		WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})

add_custom_target(archive
		COMMAND git archive HEAD -o ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}-`git describe --abbrev=4 HEAD`.tar.gz
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
