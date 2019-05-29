cmake_minimum_required(VERSION 3.12)
project(math_search)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(math_search
        src/file_path.h
        src/interface.h
        src/lex.cpp
        src/lex.h
        test/main.cpp
        src/segment.cpp
        src/segment.h
        src/query_result.h
        src/query_type.h
        src/store.cpp
        src/store.h
        src/struct_tree.h
        src/text.cpp
        src/text.h
        src/tree.cpp
        src/tree.h
        src/utf.cpp
        src/utf.h
        src/util.cpp
        src/util.h
        src/cmd.cpp
        src/cmd.h
        src/keyword.h
        src/keyword.cpp
        src/word.h
        src/word_query.cpp
        src/word_query.h
        src/word_segment.cpp
        src/word_segment.h
        src/segment_words_impl.cpp
        src/query_comm_impl.cpp
        )
