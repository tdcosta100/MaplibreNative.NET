cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/dependencies/maplibre-native/platform/windows/custom-toolchain.cmake)

project("MaplibreNative.NET" LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)

if(NOT MSVC)
	return()
endif()

add_library(mbgl-dotnet SHARED)

set(ASSEMBLY_NAME "MaplibreNative.NET")

set_target_properties(
	mbgl-dotnet
	PROPERTIES
		COMMON_LANGUAGE_RUNTIME ""
		OUTPUT_NAME ${ASSEMBLY_NAME}
)

target_compile_options(mbgl-dotnet PRIVATE "/doc")

if(CMAKE_GENERATOR STREQUAL "Ninja")
	string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
	string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
	target_compile_options(mbgl-dotnet PRIVATE "/clr" "/EHa")

	add_custom_command(
		TARGET mbgl-dotnet
		POST_BUILD
		COMMAND xdcmake *.xdc /nologo /assembly:"${ASSEMBLY_NAME}" /out:"${ASSEMBLY_NAME}.xml"
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
		VERBATIM
	)
endif()

target_compile_definitions(
	mbgl-dotnet
	PRIVATE
		_USE_MATH_DEFINES
		NOMINMAX
		DOTNET_NAMESPACE=MaplibreNative
)

if(MLN_WITH_EGL)
	target_compile_definitions(mbgl-dotnet PRIVATE MLN_WITH_EGL)
elseif(MLN_WITH_OSMESA)
	target_compile_definitions(mbgl-dotnet PRIVATE MLN_WITH_OSMESA)
	target_include_directories(mbgl-dotnet PRIVATE ${PROJECT_SOURCE_DIR}/dependencies/maplibre-native/platform/windows/vendor/mesa3d/include)
endif()

target_sources(
	mbgl-dotnet
	PRIVATE
	${PROJECT_SOURCE_DIR}/src/AlphaImage.cpp
	${PROJECT_SOURCE_DIR}/src/AnimationOptions.cpp
	${PROJECT_SOURCE_DIR}/src/AsyncRequest.cpp
	${PROJECT_SOURCE_DIR}/src/BackendScope.cpp
	${PROJECT_SOURCE_DIR}/src/BoundOptions.cpp
	${PROJECT_SOURCE_DIR}/src/CameraOptions.cpp
	${PROJECT_SOURCE_DIR}/src/CanonicalTileID.cpp
	${PROJECT_SOURCE_DIR}/src/ClientOptions.cpp
	${PROJECT_SOURCE_DIR}/src/EdgeInsets.cpp
	${PROJECT_SOURCE_DIR}/src/ExternalRenderingContextBackend.cpp
	${PROJECT_SOURCE_DIR}/src/ExternalRenderingContextFrontend.cpp
	${PROJECT_SOURCE_DIR}/src/FileSource.cpp
	${PROJECT_SOURCE_DIR}/src/FileSourceManager.cpp
	${PROJECT_SOURCE_DIR}/src/FreeCameraOptions.cpp
	${PROJECT_SOURCE_DIR}/src/GeoJSON.cpp
	${PROJECT_SOURCE_DIR}/src/HeadlessFrontend.cpp
	${PROJECT_SOURCE_DIR}/src/Image.cpp
	${PROJECT_SOURCE_DIR}/src/LatLng.cpp
	${PROJECT_SOURCE_DIR}/src/Map.cpp
	${PROJECT_SOURCE_DIR}/src/MapObserver.cpp
	${PROJECT_SOURCE_DIR}/src/MapOptions.cpp
	${PROJECT_SOURCE_DIR}/src/OverscaledTileID.cpp
	${PROJECT_SOURCE_DIR}/src/PremultipliedImage.cpp
	${PROJECT_SOURCE_DIR}/src/ProjectionMode.cpp
	${PROJECT_SOURCE_DIR}/src/Renderer.cpp
	${PROJECT_SOURCE_DIR}/src/RendererBackend.cpp
	${PROJECT_SOURCE_DIR}/src/RendererObserver.cpp
	${PROJECT_SOURCE_DIR}/src/RenderingStats.cpp
	${PROJECT_SOURCE_DIR}/src/Resource.cpp
	${PROJECT_SOURCE_DIR}/src/ResourceOptions.cpp
	${PROJECT_SOURCE_DIR}/src/ResourceTransform.cpp
	${PROJECT_SOURCE_DIR}/src/Response.cpp
	${PROJECT_SOURCE_DIR}/src/RunLoop.cpp
	${PROJECT_SOURCE_DIR}/src/Shader.cpp
	${PROJECT_SOURCE_DIR}/src/ShaderRegistry.cpp
	${PROJECT_SOURCE_DIR}/src/Size.cpp
	${PROJECT_SOURCE_DIR}/src/Style.cpp
	${PROJECT_SOURCE_DIR}/src/TileCoordinate.cpp
	${PROJECT_SOURCE_DIR}/src/TransformState.cpp
	${PROJECT_SOURCE_DIR}/src/UnassociatedImage.cpp
	${PROJECT_SOURCE_DIR}/src/UnitBezier.cpp
	${PROJECT_SOURCE_DIR}/src/UnwrappedTileID.cpp
	${PROJECT_SOURCE_DIR}/src/UpdateParameters.cpp
	${PROJECT_SOURCE_DIR}/src/Value.cpp
	${PROJECT_SOURCE_DIR}/src/Vector.cpp
)

target_include_directories(
	mbgl-dotnet
	PRIVATE
		${PROJECT_SOURCE_DIR}/include
		${PROJECT_SOURCE_DIR}/dependencies/maplibre-native/src
)

add_subdirectory(${PROJECT_SOURCE_DIR}/dependencies/maplibre-native EXCLUDE_FROM_ALL)

find_package(libuv REQUIRED)

target_link_libraries(
	mbgl-dotnet
	PRIVATE
		Mapbox::Map
		uv_a
)
