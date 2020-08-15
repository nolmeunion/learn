project(learn_asio)

add_executable(timer deadline_timer.cpp)
target_link_libraries(timer boost_system)