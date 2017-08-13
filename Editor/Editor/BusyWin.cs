using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Security.Permissions;

namespace Editor
{
	public partial class BusyWin : Form
	{
		[SecurityPermission(SecurityAction.LinkDemand, Flags = SecurityPermissionFlag.UnmanagedCode)]
		protected override void WndProc(ref Message m)
		{
			const int WM_SYSCOMMAND = 0x112;
			const long SC_CLOSE = 0xF060L;

			if (m.Msg == WM_SYSCOMMAND && (m.WParam.ToInt64() & 0xFFF0L) == SC_CLOSE)
			{
				return;
			}
			base.WndProc(ref m);
		}

		public BusyWin(string title, string message)
		{
			InitializeComponent();

			this.Text = title;
			this.Message.Text = message;
		}
		public BusyWin(string title)
			: this(title, "しばらくお待ち下さい...")
		{ }
		public BusyWin()
			: this("処理中")
		{ }

		private ThreadStart Runner;
		private bool Death;
		private Exception R_Ex;

		public void Perform(ThreadStart runner)
		{
			this.Runner = runner;
			new Thread(this.CallRunner).Start();

			this.ShowDialog();

			if (this.R_Ex != null)
			{
				Tools.DispError(this.R_Ex);
			}
		}
		private void CallRunner()
		{
			try
			{
				this.Runner();
			}
			catch (Exception e)
			{
				this.R_Ex = e;
			}
			this.Death = true;
		}

		private void MainTimer_Tick(object sender, EventArgs e)
		{
			if (this.Death)
			{
				this.Close();
			}
			lock (SYNCROOT)
			{
				if (_Message != null)
				{
					this.Message.Text = _Message;
					_Message = null;
				}
			}
		}

		private static object SYNCROOT = new object();
		private static string _Message;

		public static void SetMessage(string message)
		{
			lock (SYNCROOT)
			{
				_Message = message;
			}
		}

		private void BusyWin_Load(object sender, EventArgs e)
		{ }
	}
}
