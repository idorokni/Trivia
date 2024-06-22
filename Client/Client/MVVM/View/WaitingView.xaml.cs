using Client.MVVM.Model;
using Client.MVVM.ViewModel;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Client.MVVM.View
{
    /// <summary>
    /// Interaction logic for WaitingView.xaml
    /// </summary>
    public partial class WaitingView : UserControl
    {

        private BackgroundWorker background_worker = new BackgroundWorker();
        private bool _isDisposed = false;
        public WaitingView()
        {
            InitializeComponent();

            background_worker.WorkerSupportsCancellation = true;
            background_worker.WorkerReportsProgress = true;

            background_worker.DoWork += background_worker_DoWork;
            background_worker.RunWorkerCompleted += background_worker_RunWorkerCompleted;

            StartHeadOnGameRequest startHeadOnGameRequest = new StartHeadOnGameRequest();

            byte[] msg = App.Communicator.Serialize(startHeadOnGameRequest, (int)Client.MVVM.Model.RequestCode.START_HEAD_ON_GAME_REQUEST_CODE);
            App.Communicator.SendMessage(msg);

            RequestResult response = App.Communicator.DeserializeMessage();
            // Handle the response here (e.g., check if login was successful)

            if (response.Data.Contains("\"status\":1"))
            {
                StartStoryboard();
            }
            else if (response.Data.Contains("\"status\":2"))
            {
                background_worker.RunWorkerAsync(3000);
            }
            else
            {
                MessageBox.Show("Joinroom failed: " + response.Data);
            }
        }

        private void background_worker_DoWork(object sender, DoWorkEventArgs e)
        {
            while (!background_worker.CancellationPending)
            {
                refreshScreen();
                Thread.Sleep((int)e.Argument);
            }
        }

        private void background_worker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (e.Cancelled)
            {
                //MessageBox.Show("BackgroundWorker canceled");
            }
            else
            {
                //MessageBox.Show("BackgroundWorker ended successfully");
            }
        }

        public void refreshScreen()
        {
            try
            {
                // Here should get rooms from server
                byte[] msg = new byte[] { (byte)Client.MVVM.Model.RequestCode.GET_HEAD_ON_GAME_STATE_REQUEST_CODE };
                App.Communicator.SendMessage(msg);

                RequestResult response = App.Communicator.DeserializeMessage();
                int status = int.Parse(response.Data.Split(':')[3].Split('}')[0]);
                Application.Current.Dispatcher.Invoke(() => {
                    if (int.Parse(response.Data.Split(':')[3].Split('}')[0]) == 1)
                    {
                        Dispose();
                        StartStoryboard();
                    }
                });

            }
            catch (Exception ex)
            {
                MessageBox.Show("An error occurred: " + ex.Message);
            }
        }

        public void Dispose()
        {
            if (!_isDisposed)
            {
                background_worker.CancelAsync();
                background_worker.Dispose();
                _isDisposed = true;
            }
        }



        private void Storyboard_Completed(object sender, EventArgs e)
        {
            MainViewModel.Instance.CurrentView = new _1v1ViewModel();
        }

        public void StartStoryboard()
        {
            Application.Current.Dispatcher.Invoke(() =>
            {
                Storyboard waitingStoryboard = (Storyboard)this.Resources["WaitingAnimation"];
                waitingStoryboard.Stop();
                TextBlock block = (TextBlock)this.FindName("WaitingTextBlock");
                block.Opacity = 0;
                Storyboard startingStoryboard = (Storyboard)this.Resources["StartingAnimation"];
                startingStoryboard.Begin();
            });
        }
    }
}
