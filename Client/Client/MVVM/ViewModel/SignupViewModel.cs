using Client.Core;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.MVVM.ViewModel
{
    internal class SignupViewModel : ObservableObject
    {
        private string _username;
        private string _password;
        private string _email;
        private string _address;
        private string _phone;
        private string _birthday;

        public string Username
        {
            get { return _username; }
            set { _username = value; }
        }
        
        public string Password
        {
            get { return _password; }
            set { _password = value; }
        }
        
        public string Email
        {
            get { return _email; }
            set { _email = value; }
        }
        
        public string Address
        {
            get { return _address; }
            set { _address = value; }
        }

        public string Phone
        {
            get { return _phone; }
            set { _phone = value; }
        }

        public string Birthday
        {
            get { return _birthday; }
            set { _birthday = value; }
        }

        public RelayCommand SubmitSignupCommand {  get; set; }

        public SignupViewModel()
        {
            SubmitSignupCommand = new RelayCommand(o =>
            {
                Console.WriteLine(Username + " " + Password + " " + Email + " " + Address + " " + Birthday + " " + Phone);
                MainViewModel.Instance.CurrentView = new HomeViewModel();
            }, o => !string.IsNullOrEmpty(Username) && !string.IsNullOrEmpty(Password) && !string.IsNullOrEmpty(Phone) && !string.IsNullOrEmpty(Birthday) && !string.IsNullOrEmpty(Email));
        }

    }
}
