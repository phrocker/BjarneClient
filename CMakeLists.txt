project(bjarneclient)

add_executable(bjarneclient src/data/constructs/scanstate.cpp src/data/constructs/column.cpp src/data/constructs/client/zookeeper/watch.cpp src/data/constructs/client/zookeeper/zookeepers.cpp src/data/constructs/client/zookeeperinstance.cpp main.cpp)

install(TARGETS bjarneclient RUNTIME DESTINATION bin)

add_subdirectory(test)
add_subdirectory(src/data/constructs/client/zookeeper)
add_subdirectory(src/data/constructs/client/zookeeper)