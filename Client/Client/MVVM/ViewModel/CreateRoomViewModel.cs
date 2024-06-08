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
    internal class CreateRoomViewModel : ObservableObject
    {
        private string _name;
        private string _amountOfUsers;
        private string _amountOfQuestions;
        private string _timePerQuestions;

        public string Name
        {
            get { return _name; }
            set { _name = value; }
        }

        public string AmountOfUsers
        {
            get { return _amountOfUsers; }
            set { _amountOfUsers = value; }
        }

        public string AmountOfQuestions
        {
            get { return _amountOfQuestions; }
            set { _amountOfQuestions = value; }
        }

        public string TimePerQuestions
        {
            get { return _timePerQuestions; }
            set { _timePerQuestions = value; }
        }

        public RelayCommand SubmitCreateRoomCommand { get; set; }

        public CreateRoomViewModel()
        {
            SubmitCreateRoomCommand = new RelayCommand(o => ExecuteCreateRoomModel(), o => CanExecuteCreateRoomModel());
        }

        private bool CanExecuteCreateRoomModel()
        {
            if (!string.IsNullOrEmpty(Name) && !string.IsNullOrEmpty(AmountOfQuestions) && !string.IsNullOrEmpty(AmountOfUsers) && !string.IsNullOrEmpty(TimePerQuestions))
            {
                return UInt32.TryParse(AmountOfQuestions, out _) && UInt32.TryParse(AmountOfUsers, out _) && UInt32.TryParse(TimePerQuestions, out _);
            }
            return false;
        }

        private void ExecuteCreateRoomModel()
        {
            try
            {
                CreateRoomRequest CreateroomRequest = new CreateRoomRequest(Name, UInt32.Parse(AmountOfUsers), UInt32.Parse(AmountOfQuestions), UInt32.Parse(TimePerQuestions));

                byte[] msg = App.Communicator.Serialize(CreateroomRequest, (int)Client.MVVM.Model.RequestCode.CREATE_ROOM_REQUEST_CODE);
                App.Communicator.SendMessage(msg);

                RequestResult response = App.Communicator.DeserializeMessage();
                // Handle the response here (e.g., check if signup was successful)

                if (response.IsSuccess)
                {
                    MessageBox.Show("Create Room successful!");
                    MainViewModel.Instance.CurrentView = new HomeViewModel();
                }
                else
                {
                    MessageBox.Show("Create Room failed: " + response.Data);
                }
             
            }
            catch (Exception ex)
            {
                MessageBox.Show("An error occurred: " + ex.Message);
            }
        }
    }
}
