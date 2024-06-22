using Client.Core;
using Client.MVVM.Model;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Client.MVVM.ViewModel
{
    internal class WaitingViewModel : ObservableObject
    {
        public WaitingViewModel()
        {
            StartHeadOnGameRequest startHeadOnGameRequest = new StartHeadOnGameRequest();

            byte[] msg = App.Communicator.Serialize(startHeadOnGameRequest, (int)Client.MVVM.Model.RequestCode.START_HEAD_ON_GAME_REQUEST_CODE);
            App.Communicator.SendMessage(msg);

            RequestResult response = App.Communicator.DeserializeMessage();
            // Handle the response here (e.g., check if login was successful)

            if (response.Data.Contains("\"status\":1"))
            {
                MainViewModel.Instance.CurrentView = new _1v1ViewModel();
            }
            else if (response.Data.Contains("\"status\":2"))
            {

            }
            else
            {
                MessageBox.Show("Joinroom failed: " + response.Data);
            }
        }
    }
}
