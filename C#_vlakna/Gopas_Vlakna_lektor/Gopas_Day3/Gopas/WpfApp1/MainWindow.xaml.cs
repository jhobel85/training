using System;
using System.Collections.Generic;
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
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        SemaphoreSlim _sem;
        int cnt;

        public MainWindow()
        {
            InitializeComponent();
            _sem = new SemaphoreSlim(1, 1);
        }

        private async void Button_Click(object sender, RoutedEventArgs e)
        {
            button.Content = cnt++;
            await _sem.WaitAsync();
            await GetResponse();
            _sem.Release();
            button.Content = cnt--;
        }

        //void Block(Func<Task> f)
        //{
        //    Task.Run(() => f()).Wait();
        //}

        async Task GetResponse()
        {
            await Task.Delay(10000);
        }
    }
}
