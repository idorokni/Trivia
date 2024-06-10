using Client.Core;
using Client.MVVM.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Client.MVVM.ViewModel
{
    internal class UserStatsViewModel : ObservableObject
    {
        private string _name;
        private string _avgAnswerTime;
        private string _numOfCorrectAnswers;
        private string _numOfTotalAnswers;
        private string _numOfGamesPlayed;

        public string Name {  get { return _name; } set { _name = value; } }
        public string AvgAnswerTime { get { return _avgAnswerTime; } set { _avgAnswerTime = value; } }
        public string NumOfCorrectAnswers { get { return _numOfCorrectAnswers; } set { _numOfCorrectAnswers = value; } }
        public string NumOfTotalAnswers { get { return _numOfTotalAnswers; } set { _numOfTotalAnswers = value; } }
        public string NumOfGamesPlayed { get { return _numOfGamesPlayed; } set { _numOfGamesPlayed = value; } }

        public UserStatsViewModel()
        {
            try
            {
                _name = MainViewModel.Instance.Username;
                UserStatisticsRequest UserStatisticsRequest = new UserStatisticsRequest();

                byte[] msg = App.Communicator.Serialize(UserStatisticsRequest, (int)Client.MVVM.Model.RequestCode.GET_USER_STATISTICS_REQUEST_CODE);
                App.Communicator.SendMessage(msg);

                RequestResult response = App.Communicator.DeserializeMessage();
                // Handle the response here (e.g., check if signup was successful)

                if (response.IsSuccess)
                {
                   // _avgAnswerTime = response.Data
                }
                else
                {
                    MessageBox.Show("SignUp failed: " + response.Data);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("An error occurred: " + ex.Message);
            }
        }
    }
}
