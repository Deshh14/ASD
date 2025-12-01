add_executable(LabaArithmetic
    calculator.cpp
    expression.cpp
    main.cpp
    parser.cpp
)

# Подключаем зависимости
target_link_libraries(LabaArithmetic
    Stack
    List
    TVector
)

# Указываем пути к заголовочным файлам зависимостей
target_include_directories(LabaArithmetic PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib_stack
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib_list
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib_TVector
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Настройки компиляции C++
set_target_properties(LabaArithmetic PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)