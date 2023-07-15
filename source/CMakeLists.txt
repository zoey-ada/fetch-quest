
add_subdirectory(libraries)

include_directories(
	${CMAKE_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
)

set(srcs
	entities/components/movementComponent2d.hpp
	entities/components/movementComponent2d.cpp

	engine.hpp

	fetchQuestLogic.hpp
	fetchQuestLogic.cpp

	main.cpp
)

add_executable(fetch-quest WIN32 ${srcs})
add_dependencies(fetch-quest assets)

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

# -------------------------------------------------------------------------------
# config files
# -------------------------------------------------------------------------------
set(config_files
	command_list.json
	engine_settings.json
	input_config.json
	physics_config.json
)

# source_group(config_files FILES ${config_files})

foreach(config_file ${config_files})
	_zag_copy_file(${config_file} ${bin_dir} custom_target copied_file)

	set(copied_files ${copied_files} ${copied_file})
	set(copy_targets ${copy_targets} ${custom_target})

	set_target_properties(${custom_target} PROPERTIES FOLDER file_copies/config)
endforeach(config_file ${config_files})

add_dependencies(fetch-quest
	${copy_targets}
)

# add_custom_command(
# 	TARGET fetch-quest POST_BUILD
# 	COMMAND ${CMAKE_COMMAND} -E copy
# 	${CMAKE_CURRENT_SOURCE_DIR}/engine_settings.json
# 	${bin_dir}/engine_settings.json)
