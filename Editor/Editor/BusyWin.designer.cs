namespace Editor
{
	partial class BusyWin
	{
		/// <summary>
		/// 必要なデザイナ変数です。
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		/// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows フォーム デザイナで生成されたコード

		/// <summary>
		/// デザイナ サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディタで変更しないでください。
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			this.PB1 = new System.Windows.Forms.ProgressBar();
			this.Message = new System.Windows.Forms.Label();
			this.MainTimer = new System.Windows.Forms.Timer(this.components);
			this.SuspendLayout();
			// 
			// PB1
			// 
			this.PB1.Location = new System.Drawing.Point(12, 50);
			this.PB1.Name = "PB1";
			this.PB1.Size = new System.Drawing.Size(370, 20);
			this.PB1.Style = System.Windows.Forms.ProgressBarStyle.Marquee;
			this.PB1.TabIndex = 0;
			// 
			// Message
			// 
			this.Message.AutoSize = true;
			this.Message.Location = new System.Drawing.Point(20, 20);
			this.Message.Name = "Message";
			this.Message.Size = new System.Drawing.Size(29, 12);
			this.Message.TabIndex = 1;
			this.Message.Text = "----";
			// 
			// MainTimer
			// 
			this.MainTimer.Enabled = true;
			this.MainTimer.Tick += new System.EventHandler(this.MainTimer_Tick);
			// 
			// BusyWin
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(394, 82);
			this.ControlBox = false;
			this.Controls.Add(this.Message);
			this.Controls.Add(this.PB1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "BusyWin";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "----";
			this.Load += new System.EventHandler(this.BusyWin_Load);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.ProgressBar PB1;
		private System.Windows.Forms.Label Message;
		private System.Windows.Forms.Timer MainTimer;
	}
}
