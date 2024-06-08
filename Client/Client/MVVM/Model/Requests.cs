using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
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

    public class Request
    {

    }
    public class LoginRequest : Request
    {
        public string username;
        public string password;

        public LoginRequest(string username, string password)
        {
            this.username = username;
            this.password = password;
        }

    }

    public class SignUpRequest : Request
    {
        public string username;
        public string password;
        public string mail;
        public string address;
        public string phone;
        public string birthday;

        public SignUpRequest(string username, string password, string mail, string address, string phone, string birthday)
        {
            this.username = username;
            this.password = password;
            this.mail = mail;
            this.address = address;
            this.phone = phone;
            this.birthday = birthday;
        }
    }

    public class GetPlayersInRoomRequest : Request
    {
        public uint roomId;
        public GetPlayersInRoomRequest(uint roomId)
        {
            this.roomId = roomId;
        }
    }
    
    public class JoinRoomRequest : Request
    {
        public uint roomId;
        public JoinRoomRequest(uint roomId)
        {
            this.roomId = roomId;
        }
    }
    
    public class CreateRoomRequest : Request
    {
        public string roomName;
        public uint maxUsers;
        public uint questionCount;
        public uint answerTimeout;

        public CreateRoomRequest(string roomName, uint maxUsers, uint questionCount, uint answerTimeout)
        {
            this.roomName = roomName;
            this.maxUsers = maxUsers;
            this.questionCount = questionCount;
            this.answerTimeout = answerTimeout;
        }
    }

    public class RequestResult
    {
        public int code;
        public string Data { get; set; }
        public bool IsSuccess;

        public RequestResult(int code, string data)
        {
            this.code = code;
            this.Data = data;
            if (data.Contains("\"status\":1")) this.IsSuccess = true;
            else this.IsSuccess = false;
        }
    }
}
