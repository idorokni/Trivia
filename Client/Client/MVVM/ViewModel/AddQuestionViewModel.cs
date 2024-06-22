using Client.Core;
using Client.MVVM.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Xml.Linq;

namespace Client.MVVM.ViewModel
{
    internal class AddQuestionViewModel : ObservableObject
    {
        public string Question { get; set; }
        public string CorrectAnswer { get; set; }
        public string WrongAnswer1 { get; set; }
        public string WrongAnswer2 { get; set; }
        public string WrongAnswer3 { get; set; }


        public RelayCommand AddQuestionCommand { get; set; }

        public AddQuestionViewModel()
        {
            AddQuestionCommand = new RelayCommand(o => ExecuteAddQuestionModel(), o => CanExecuteAddQuestionModel());
        }

        private bool CanExecuteAddQuestionModel()
        {
            return (!string.IsNullOrEmpty(Question) && !string.IsNullOrEmpty(CorrectAnswer) && !string.IsNullOrEmpty(WrongAnswer1) && !string.IsNullOrEmpty(WrongAnswer2) && !string.IsNullOrEmpty(WrongAnswer3));
        }

        private void ExecuteAddQuestionModel()
        {
            try
            {
                AddQuestionRequest addQuestionRequest = new AddQuestionRequest(Question, CorrectAnswer, WrongAnswer1, WrongAnswer2, WrongAnswer3);

                byte[] msg = App.Communicator.Serialize(addQuestionRequest, (int)Client.MVVM.Model.RequestCode.ADD_QUESTION_REQUEST_CODE);
                App.Communicator.SendMessage(msg);

                RequestResult response = App.Communicator.DeserializeMessage();
                // Handle the response here (e.g., check if signup was successful)

                if (response.IsSuccess)
                {
                    MessageBox.Show("Added Question Successfuly!");
                    MainViewModel.Instance.CurrentView = new HomeViewModel();
                }
                else
                {
                    MessageBox.Show("Added Question failed: " + response.Data.Substring("{\"error\":\"".Length, response.Data.Length - "{\"error\":\"".Length - "\",\"status\":0}".Length));
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("An error occurred: " + ex.Message);
            }
        }
    }
}
