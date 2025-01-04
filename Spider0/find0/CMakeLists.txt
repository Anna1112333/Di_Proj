cmake_minimum_required(VERSION 3.22.0) #версия cmake

project(find0)  #название проекта
set(PostgreSQL_ADDITIONAL_VERSIONS "15")
add_subdirectory("C:/Dock/PSQ 001/c_pq/libpqxx-7.8.1" lib_find0) 
#добавляю библиотеку и называю её libc_pq \ заменяем на /
add_executable(find0 find_1.cpp "sql_query.h" "sql_query.cpp")  #ресуры
target_compile_features(find0 PRIVATE cxx_std_17) # стандарт 17 для с++
target_link_libraries(find0 pqxx) #линкуем