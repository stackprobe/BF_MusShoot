using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Threading;

namespace Editor
{
	static class Program
	{
		/// <summary>
		/// アプリケーションのメイン エントリ ポイントです。
		/// </summary>
		[STAThread]
		static void Main()
		{
			Application.ThreadException += new ThreadExceptionEventHandler(Application_ThreadException);
			AppDomain.CurrentDomain.UnhandledException += new UnhandledExceptionEventHandler(CurrentDomain_UnhandledException);

			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault(false);
			Application.Run(new MainWin());
		}

		private static void Application_ThreadException(object sender, ThreadExceptionEventArgs e)
		{
			try
			{
				Tools.DispError(e.Exception, "Application_ThreadException");
			}
			catch
			{ }

			Environment.Exit(1);
		}
		private static void CurrentDomain_UnhandledException(object sender, UnhandledExceptionEventArgs e)
		{
			try
			{
				Tools.DispError("" + e.ExceptionObject, "CurrentDomain_UnhandledException");
			}
			catch
			{ }

			Environment.Exit(2);
		}
	}
}
