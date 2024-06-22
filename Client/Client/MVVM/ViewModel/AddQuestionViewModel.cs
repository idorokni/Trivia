using Client.Core;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.MVVM.ViewModel
{
    internal class AddQuestionViewModel : ObservableObject
    {
        public string CorrectAnswer { get; set; }
        public AddQuestionViewModel() { }
    }
}
