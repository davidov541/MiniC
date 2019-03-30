using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Forms;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;

namespace Emulator
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private BitEpicness _processor;
        public BitEpicness Processor
        {
            get { return _processor; }
            set { _processor = value; }
        }

        public MainWindow()
        {
            this._processor = new BitEpicness(new Dictionary<String, short>());
            this.DataContext = this._processor;
            InitializeComponent();
            this.txtConsole.Text = this._processor.ToString();
        }

        private void btnEvalOne_Click(object sender, RoutedEventArgs e)
        {
            this._processor.evaluateAsmInstruction(txtInstruction.Text);
            this.txtConsole.Text = this._processor.ToString();
        }

        private void txtASMFile_GotFocus(object sender, RoutedEventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Multiselect = false;
            ofd.CheckFileExists = true;
            ofd.CheckPathExists = true;
            ofd.ShowDialog();
            this.txtASMFile.Text = ofd.FileName;
        }

        private void btnASMFile_Click(object sender, RoutedEventArgs e)
        {
            if (this.txtASMFile.Text.Length > 0)
            {
                FileStream fs = new FileStream(this.txtASMFile.Text, FileMode.Open, FileAccess.Read);
                StreamReader sr = new StreamReader(fs);
                String code = sr.ReadToEnd();
                this.txtCode.Text = code;
                code = code.Replace("\r", "");
                short instNumber = -1;
                foreach (String line in code.Split('\n'))
                {
                    String str = line;
                    for (int i = 1; i < str.Length; i++)
                    {
                        if (str[i] == '/' && str[i - 1] == '/')
                        {
                            str = str.Remove(i - 1);
                            break;
                        }
                    }
                    if (str.Contains(':'))
                    {
                        String[] parts = str.Split(':');
                        str = parts[1];
                        this._processor.Labels[parts[0]] = instNumber;
                    }
                    if (!str.Equals(""))
                    {
                        this._processor.FirmwareValues.Add(str);
                        instNumber++;
                    }
                }
            }
            this._processor.RegisterInformation[this._processor.getRegisterNum("$ra")].Value = this._processor.FirmwareValues.Count + 1;
        }

        private void btnStep_Click(object sender, RoutedEventArgs e)
        {
            this._processor.Step();
            this.txtConsole.Text = this._processor.ToString();
        }

        private void btnReset_Click(object sender, RoutedEventArgs e)
        {
            this._processor = new BitEpicness(new Dictionary<String, short>());
            this.txtConsole.Text = this._processor.ToString();
            this.txtASMFile.Text = "";
        }

        private void btnRun_Click(object sender, RoutedEventArgs e)
        {
            this._processor.Run();
            this.txtConsole.Text = this._processor.ToString();
        }
    }
}
