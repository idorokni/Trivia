#pragma once

constexpr auto LOGIN_REQUEST_CODE = 51;
constexpr auto SIGNUP_REQUEST_CODE = 52;

constexpr auto CODE_AMOUNT_BYTES = 1;
constexpr auto BYTES_LENGTH = 4;
constexpr auto HEADER_LENGTH = CODE_AMOUNT_BYTES + BYTES_LENGTH;
