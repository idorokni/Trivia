﻿using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Security.RightsManagement;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Markup;

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
        GET_USER_STATISTICS_REQUEST_CODE = 59,
        CLOSE_ROOM_REQUEST_CODE = 60,
        START_GAME_REQUEST_CODE = 61,
        GET_ROOM_STATE_REQUEST_CODE = 62,
        LEAVE_ROOM_REQUEST_CODE = 63,
        LEAVE_GAME_REQUEST_CODE = 64,
        GET_QUESTION_REQUEST_CODE = 65,
        SUBMIT_ANSWER_REQUEST_CODE = 66,
        GET_GAME_RESULT_REQUEST_CODE = 67,
        GET_HEAD_ON_GAME_STATE_REQUEST_CODE = 68,
        START_HEAD_ON_GAME_REQUEST_CODE = 69,
        ADD_QUESTION_REQUEST_CODE = 70
    };

    enum ResultCode
    {
        GET_QUESTION_RESPONSE = 116
    }

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

    public class UserStatisticsRequest : Request
    {
        public UserStatisticsRequest() { }
    }

    public class HighScoreRequest : Request
    {
        public HighScoreRequest() { }
    }

    public class GetRoomStateRequest : Request
    {
        public GetRoomStateRequest() { }
    }

    public class LeaveRoomRequest : Request
    {
        public LeaveRoomRequest() { }
    }

    public class CloseRoomRequest : Request
    {
        public CloseRoomRequest() { }
    }

    public class StartGameRequest : Request
    {
        public StartGameRequest() { }
    }

    public class LogoutRequest : Request
    {
        public LogoutRequest() { }
    }

    public class LeaveGameRequest : Request
    {
        public LeaveGameRequest() { }
    }

    public class GetQuestionRequest : Request
    {
        public GetQuestionRequest() { }
    }

    public class GetGameResultsRequest : Request
    {
        public GetGameResultsRequest() { }
    }

    public class SubmitAnswerRequest : Request
    {
        public uint _answerId;
        public uint _timeToAnswer;

        public SubmitAnswerRequest(uint answerId, uint timeToAnswer)
        {
            _answerId = answerId;
            _timeToAnswer = timeToAnswer;
        }
    }

    public class AddQuestionRequest : Request
    {
        public string _question;
        public string _correctAnswer;
        public string _wrongAnswer1;
        public string _wrongAnswer2;
        public string _wrongAnswer3;

        public AddQuestionRequest(string question, string correctAnswer, string wrongAnswer1, string wrongAnswer2, string wrongAnswer3)
        {
            _question = question;
            _correctAnswer = correctAnswer;
            _wrongAnswer1 = wrongAnswer1;
            _wrongAnswer2 = wrongAnswer2;
            _wrongAnswer3 = wrongAnswer3;
        }
    }

    public class StartHeadOnGameRequest : Request
    {
        public StartHeadOnGameRequest() { }
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

    public class GetQuestionResult
    {
        public int code;
        public string question { get; set; }
        public string[] answers { get; set; }
        public bool IsSuccess;


        public GetQuestionResult(int code, string data)
        {
            if (data.Contains("\"status\":1")) 
            {
                this.IsSuccess = true;
                dynamic jsonObject = JsonConvert.DeserializeObject(data);
                // Accessing question and answers
                string answersString = jsonObject.answers;
                // Splitting answers by comma
                string[] answersArray = answersString.Split(',');
                this.code = code;
                this.question = jsonObject.question;
                this.answers = answersArray;
            }
            else this.IsSuccess = false;
        }
    }
}
