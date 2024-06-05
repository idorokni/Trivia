using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Client.MVVM.Model
{
    enum RequestCode
    {
        LOGIN_REQUEST_CODE = 51,
        SIGNUP_REQUEST_CODE = 52,
        GET_PLAYERS_IN_ROOM_REQUEST_CODE = 53,
        CREATE_ROOM_REQUEST_CODE = 54,
        JOIN_ROOM_REQUEST_CODE = 55,
        HIGH_SCORE_REQUEST_CODE = 56,
        LOGOUT_REQUEST_CODE = 57,
        GET_ROOMS_REQUEST_CODE = 58,
        GET_USER_STATISTICS_REQUEST_CODE = 59
    };

    public class LoginRequest
    {
        public string username;
        public string password;

        public LoginRequest(string username, string password)
        {
            this.username = username;
            this.password = password;
        }

    }

    public class RequestResult
    {
        public int code;
        public string Data { get; set; }

        public RequestResult(int code, string data)
        {
            this.code = code;
            this.Data = data;
        }
    }
}
