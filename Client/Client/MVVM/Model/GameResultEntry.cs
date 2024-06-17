using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.MVVM.Model
{
    internal class GameResultEntry
    {
        public string Username { get; set; }
        public uint CorrectAnswers { get; set; }
        public uint WrongAnswers { get; set; }
        public uint AverageAnswerTime { get; set; }
    }
}
