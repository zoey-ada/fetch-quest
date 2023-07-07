
add_subdirectory(libraries)

include_directories(
	${CMAKE_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
)

set(srcs
	engine.hpp

	fetchQuestLogic.hpp
	fetchQuestLogic.cpp

	main.cpp
)

add_executable(fetch-quest WIN32 ${srcs})

link_static(fetch-quest)
warnings_as_errors(fetch-quest)

target_link_libraries(fetch-quest
	PRIVATE
		platypus-proto
		platypus
)

if(WITH_COVERAGE)
	if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_compile_options(fetch-quest
			PRIVATE
				-fprofile-instr-generate -fcoverage-mapping
		)
	elseif(CMAKE_CSS_COMPILER_ID STREQUAL "MSVC")
		target_compile_options(fetch-quest
			PRIVATE
				/fsanitize-coverage=inline-8bit-counters
		)
	endif()
endif()

# add_custom_command(
# 	TARGET fetch-quest POST_BUILD
# 	COMMAND ${CMAKE_COMMAND} -E copy
# 	${CMAKE_CURRENT_SOURCE_DIR}/engine_settings.json
# 	${bin_dir}/engine_settings.json)
