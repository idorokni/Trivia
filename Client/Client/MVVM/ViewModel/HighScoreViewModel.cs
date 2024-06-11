using Client.Core;
using Client.MVVM.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Xml.Linq;

namespace Client.MVVM.ViewModel
{
    internal class HighScoreViewModel : ObservableObject
    {
        private ScoreModel _firstScore;
        private ScoreModel _secondScore;
        private ScoreModel _thirdScore;
        private ScoreModel _fourthScore;
        private ScoreModel _fifthScore;

        public ScoreModel FirstScore { get { return _firstScore; } set { _firstScore = value; } }
        public ScoreModel SecondScore { get { return _secondScore; } set { _secondScore = value; } }
        public ScoreModel ThirdScore { get { return _thirdScore; } set { _thirdScore = value; } }
        public ScoreModel FourthScore { get { return _fourthScore; } set { _fourthScore = value; } }
        public ScoreModel FifthScore { get { return _fifthScore; } set { _fifthScore = value; } }


        public HighScoreViewModel()
        {
            try
            {
                HighScoreRequest highScoreRequest = new HighScoreRequest();
                int count = 0;
                ScoreModel[] arr = new ScoreModel[] { _firstScore, _secondScore, _thirdScore, _fourthScore, _fifthScore };

                byte[] msg = App.Communicator.Serialize(highScoreRequest, (int)Client.MVVM.Model.RequestCode.HIGH_SCORE_REQUEST_CODE);
                App.Communicator.SendMessage(msg);

                RequestResult response = App.Communicator.DeserializeMessage();
                // Handle the response here (e.g., check if signup was successful)

                if (response.IsSuccess)
                {
                    int highScoresStartIndex = response.Data.IndexOf("highScores\":\"");
                    int statusStartIndex = response.Data.IndexOf("status");

                    if (highScoresStartIndex != -1 && statusStartIndex != -1 && highScoresStartIndex < statusStartIndex)
                    {
                        highScoresStartIndex += "highScores\":\"".Length;
                        string highScoresSubstring = response.Data.Substring(highScoresStartIndex, statusStartIndex - highScoresStartIndex - 2); // Exclude the last two characters to remove "\","
                        string[] scoresArray = highScoresSubstring.Split(',');

                        Action<ScoreModel>[] propertySetters =
                        {
                            value => _firstScore = value,
                            value => _secondScore = value,
                            value => _thirdScore = value,
                            value => _fourthScore = value,
                            value => _fifthScore = value,
                        };

                        for (int i = 0; i < scoresArray.Length && i < propertySetters.Length; i++)
                        {
                            string score = scoresArray[i];
                            if (!string.IsNullOrWhiteSpace(score) && score != "\"")
                            {
                                string[] parts = score.Split('-');
                                if (parts.Length == 2)
                                {
                                    ScoreModel model = new ScoreModel(parts[0], parts[1]);
                                    propertySetters[i](model);
                                }
                            }
                        }

                    }
                }
                else
                {
                    MessageBox.Show("scores failed: " + response.Data);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("An error occurred: " + ex.Message);
            }
        }
    }
}
