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
        public string email;
        public string address;
        public string phone;
        public string birthday;

        public SignUpRequest(string username, string password, string email, string address, string phone, string birthday)
        {
            this.username = username;
            this.password = password;
            this.email = email;
            this.address = address;
            this.phone = phone;
            this.birthday = birthday;
        }
    }

    public class GetPlayersInRoomRequest : Request
    {
        private uint roomId;
        public GetPlayersInRoomRequest(uint roomId)
        {
            this.roomId = roomId;
        }
    }
    
    public class JoinRoomRequest : Request
    {
        private uint roomId;
        public JoinRoomRequest(uint roomId)
        {
            this.roomId = roomId;
        }
    }
    
    public class CreateRoomRequest : Request
    {
        private string roomName;
        private uint maxUsers;
        private uint questionCount;
        private uint answerTimeout;

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

        public RequestResult(int code, string data)
        {
            this.code = code;
            this.Data = data;
        }
    }
}
