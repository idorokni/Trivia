using Client.Core;
using Client.MVVM.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

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
            SubmitSignupCommand = new RelayCommand(o => ExecuteSignup(), o => CanExecuteSignup());
        }

        private bool CanExecuteSignup()
        {
            return !string.IsNullOrEmpty(Username) && !string.IsNullOrEmpty(Password) && !string.IsNullOrEmpty(Phone) && !string.IsNullOrEmpty(Birthday) && !string.IsNullOrEmpty(Email) && !string.IsNullOrEmpty(Address);
        }

        private void ExecuteSignup()
        {
            try
            {
                SignUpRequest SignupRequest = new SignUpRequest(Username, Password, Email, Address, Phone, Birthday);

                byte[] msg = App.Communicator.Serialize(SignupRequest, (int)Client.MVVM.Model.RequestCode.SIGNUP_REQUEST_CODE);
                App.Communicator.SendMessage(msg);

                RequestResult response = App.Communicator.DeserializeMessage();
                // Handle the response here (e.g., check if signup was successful)

                if (response.IsSuccess)
                {
                    MessageBox.Show("SignUp successful!");
                    MainViewModel.Instance.CurrentView = new HomeViewModel();
                    MainViewModel.Instance.ButtonVisibility = Visibility.Visible;
                    MainViewModel.Instance.Username = _username;
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
