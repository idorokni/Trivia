using Client.Core;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
        }


    }
}
