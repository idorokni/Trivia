using Client.Core;
using Client.MVVM.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.MVVM.ViewModel
{
    internal class GameResultsViewModel : ObservableObject
    {
        private ObservableCollection<string> _userNames;
        private ObservableCollection<uint> _correctAnswers;
        private ObservableCollection<uint> _wrongAnswers;
        private ObservableCollection<uint> _averageAnswerTime;

        public ObservableCollection<string> Usernames {  get { return _userNames; } set { _userNames = value; OnPropertyChanged(); } }
        public ObservableCollection<uint> CorrectAnswers {  get { return _correctAnswers; } set { _correctAnswers = value; OnPropertyChanged(); } }
        public ObservableCollection<uint> WrongAnswers {  get { return _wrongAnswers; } set { _wrongAnswers = value; OnPropertyChanged(); } }
        public ObservableCollection<uint> AvgAnswerTime {  get { return _averageAnswerTime; } set { _averageAnswerTime = value; OnPropertyChanged(); } }

        public GameResultsViewModel()
        {
            Usernames = new ObservableCollection<string>();
            CorrectAnswers = new ObservableCollection<uint>();
            WrongAnswers = new ObservableCollection<uint>();
            AvgAnswerTime = new ObservableCollection<uint>();
            //should request here

            GetGameResultsRequest getGameResultsRequest = new GetGameResultsRequest();
            byte[] msg = App.Communicator.Serialize(getGameResultsRequest, (int)Client.MVVM.Model.RequestCode.GET_GAME_RESULT_REQUEST_CODE);
            App.Communicator.SendMessage(msg);

            RequestResult response = App.Communicator.DeserializeMessage();
            if (response.IsSuccess)
            {
                string data = response.Data.Split(':')[1];
                int statusPos = data.IndexOf(",\"status\"");
                data = data.Substring(1, statusPos - 2);
                string[] results = data.Split('-');
                string[] names = new string[results.Length];
                string[] correctCount = new string[results.Length];
                string[] wrongCount = new string[results.Length];
                string[] averageTime = new string[results.Length];

                for (int i = 0; i < results.Length; i++)
                {
                    names[i] = results[i].Split(',')[0];
                    correctCount[i] = results[i].Split(',')[1];
                    wrongCount[i] = results[i].Split(',')[2];
                    averageTime[i] = results[i].Split(',')[3];
                }

                foreach (string username in names)
                {
                    Usernames.Add(username);
                }

                foreach (string correct in correctCount)
                {
                    if (uint.TryParse(correct, out uint value))
                        CorrectAnswers.Add(value);
                }

                foreach (string wrong in wrongCount)
                {
                    if (uint.TryParse(wrong, out uint value))
                        WrongAnswers.Add(value);
                }

                foreach (string time in averageTime)
                {
                    if (uint.TryParse(time, out uint value))
                        AvgAnswerTime.Add(value);
                }

            }
        }
    }
}
