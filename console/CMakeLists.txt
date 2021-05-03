cmake_minimum_required(VERSION 3.0)

project(mpkg-console)

add_definitions(-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -DLARGEFILE64_SOURCE -DDL_CLEANUP -I. -I/usr/include/libxml2 -Wall -W -DNEW_INSTALL_SYSTEM -DUSE_SYSTEM_SED -DDEP_NORMALIZE -DLINUX_DEFINED)

link_libraries(mpkg nwidgets mpkgsupport)

add_executable(mpkg-core installpkg-ng2.cpp)

set_target_properties(mpkg-core PROPERTIES OUTPUT_NAME "mpkg")

add_executable(mpkg-validate validator.cpp)
add_executable(mpkg-setmeta setmeta.cpp)
add_executable(mpkg-setprofile setprofile.cpp)
add_executable(mpkg-saveprofile saveprofile.cpp)
add_executable(mpkg-listprofiles listprofiles.cpp)
add_executable(mpkg-deleteprofile deleteprofile.cpp)
add_executable(mpkg-depgraph depgraph.cpp)
add_executable(mpkg-checkdeps checkdeps.cpp)
add_executable(mpkg-altlist altlist.cpp)
add_executable(mpkg-altshow altshow.cpp)
add_executable(mpkg-quicklist quicklist.cpp)
add_executable(mpkg-checklibdeps checklibdeps.cpp)
add_executable(mpkg-maintainer maintainer.cpp)
add_executable(mpkg-spkg2abuild spkg2abuild.cpp)
add_executable(mpkg-deporder deporder.cpp)
add_executable(mpkg-fixdeps fixdeps.cpp)
add_executable(mpkg-checkconfigs checkconfig.cpp)
add_executable(mpkg-transactions transactions.cpp)
add_executable(mpkg-rollback rollback.cpp)
add_executable(mpkg-conflicts conflicts.cpp)
add_executable(mpkg-unused unused.cpp)
add_executable(mpkg-compareversions compareversions.cpp)
add_executable(mpkg-checkbackups checkbackups.cpp)
add_executable(mpkg-getopt getopt.cpp)
add_executable(mpkg-setopt setopt.cpp)
add_executable(mpkg-vercmp vercmp.cpp)

#add_executable(mpkg-collectfileindex collectfileindex.cpp)
#add_executable(mpkg-deppath deppath.cpp)
#add_executable(mpkg-depclean depclean.cpp)
#add_executable(mpkg-converttosql converttosql.cpp)

# Installation
file(GLOB aliases "${CMAKE_CURRENT_SOURCE_DIR}/aliases/mpkg-*")
file(GLOB update_all_caches "${CMAKE_CURRENT_SOURCE_DIR}/update-all-caches")

install(TARGETS mpkg-core mpkg-validate mpkg-setmeta mpkg-setprofile mpkg-saveprofile mpkg-listprofiles mpkg-deleteprofile mpkg-depgraph mpkg-checkdeps mpkg-altlist mpkg-altshow mpkg-quicklist mpkg-checklibdeps mpkg-maintainer mpkg-spkg2abuild mpkg-deporder mpkg-fixdeps mpkg-transactions mpkg-rollback mpkg-conflicts mpkg-checkconfigs mpkg-unused mpkg-compareversions mpkg-checkbackups mpkg-getopt mpkg-setopt mpkg-vercmp
		RUNTIME DESTINATION bin PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

install(FILES ${aliases} DESTINATION bin PERMISSIONS WORLD_READ WORLD_EXECUTE OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE )
install(FILES ${update_all_caches} DESTINATION bin PERMISSIONS WORLD_READ WORLD_EXECUTE OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE )
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/mpkg-importsrc" DESTINATION bin PERMISSIONS WORLD_READ WORLD_EXECUTE OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE )
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/scripts/mpkglddcheck.sh" DESTINATION libexec PERMISSIONS WORLD_READ WORLD_EXECUTE OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/scripts/mpkg_objdump_check.sh" DESTINATION libexec PERMISSIONS WORLD_READ WORLD_EXECUTE OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/mkpkg_generator.sh" DESTINATION bin PERMISSIONS WORLD_READ WORLD_EXECUTE OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/amerge" DESTINATION bin PERMISSIONS WORLD_READ WORLD_EXECUTE OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/mpkg-getabuild" DESTINATION bin PERMISSIONS WORLD_READ WORLD_EXECUTE OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/mkabuild" DESTINATION bin PERMISSIONS WORLD_READ WORLD_EXECUTE OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/mpkgsrc" DESTINATION bin PERMISSIONS WORLD_READ WORLD_EXECUTE OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/makepkg" DESTINATION /sbin PERMISSIONS WORLD_READ WORLD_EXECUTE OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/mpkg" DESTINATION ${SYSCONFDIR}/bash_completion.d)

