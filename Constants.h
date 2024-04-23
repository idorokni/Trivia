#pragma once

constexpr auto CODE_AMOUNT_BYTES = 1;
constexpr auto BYTES_LENGTH = 4;
constexpr auto HEADER_LENGTH = CODE_AMOUNT_BYTES + BYTES_LENGTH;
constexpr auto DATABASE_NAME = "TriviaDB.sqlite";
constexpr auto PASSWORD_REGEX_PATTERN = R"(^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=.*[!@$#%^&*]).{8,32}$)";
constexpr auto EMAIL_REGEX_PATTERN = R"(^[\w\.-]+@([\w-]+\.)+[\w-]{2,4}$)";
