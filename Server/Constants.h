#pragma once

constexpr auto CODE_AMOUNT_BYTES = 1;
constexpr auto BYTES_LENGTH = 4;
constexpr auto HEADER_LENGTH = CODE_AMOUNT_BYTES + BYTES_LENGTH;
constexpr auto DATABASE_NAME = "TriviaDB.sqlite";
constexpr auto PASSWORD_REGEX_PATTERN = R"(^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=.*[!@$#%^&*]).{8,32}$)";
constexpr auto EMAIL_REGEX_PATTERN = R"(^[\w\.-]+@([\w-]+\.)+[\w-]{2,4}$)";
constexpr auto ADDRESS_REGEX_PATTERN = R"(^([A-Za-z\s]+),\s(\d+),\s([A-Za-z]+)$)";
constexpr auto PHONE_REGEX_PATTERN = R"(^0\d{1,2}-\d{7}$)";
constexpr auto BIRTHDAY_REGEX_PATTERN = R"(^(0[1-9]|[1-2][0-9]|3[0-1])\.(0[1-9]|1[0-2])\.\d{4}$)";
constexpr auto DEFULT_DAMAGE = 20;
constexpr auto STARTING_HEALTH = 100;
