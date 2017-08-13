namespace BootMenu
{
	partial class MainWin
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
			this.CBDataName = new System.Windows.Forms.ComboBox();
			this.OKButton = new System.Windows.Forms.Button();
			this.MainTimer = new System.Windows.Forms.Timer(this.components);
			this.無きゃ削除 = new System.Windows.Forms.CheckBox();
			this.SuspendLayout();
			// 
			// CBDataName
			// 
			this.CBDataName.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.CBDataName.Font = new System.Drawing.Font("Verdana", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.CBDataName.FormattingEnabled = true;
			this.CBDataName.Location = new System.Drawing.Point(12, 12);
			this.CBDataName.Name = "CBDataName";
			this.CBDataName.Size = new System.Drawing.Size(300, 37);
			this.CBDataName.TabIndex = 0;
			// 
			// OKButton
			// 
			this.OKButton.Location = new System.Drawing.Point(318, 12);
			this.OKButton.Name = "OKButton";
			this.OKButton.Size = new System.Drawing.Size(100, 37);
			this.OKButton.TabIndex = 1;
			this.OKButton.Text = "起動";
			this.OKButton.UseVisualStyleBackColor = true;
			this.OKButton.Click += new System.EventHandler(this.OKButton_Click);
			// 
			// MainTimer
			// 
			this.MainTimer.Enabled = true;
			this.MainTimer.Tick += new System.EventHandler(this.MainTimer_Tick);
			// 
			// 無きゃ削除
			// 
			this.無きゃ削除.AutoSize = true;
			this.無きゃ削除.Location = new System.Drawing.Point(318, 64);
			this.無きゃ削除.Name = "無きゃ削除";
			this.無きゃ削除.Size = new System.Drawing.Size(99, 16);
			this.無きゃ削除.TabIndex = 2;
			this.無きゃ削除.Text = "新規のとき削除";
			this.無きゃ削除.UseVisualStyleBackColor = true;
			// 
			// MainWin
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(434, 92);
			this.Controls.Add(this.無きゃ削除);
			this.Controls.Add(this.OKButton);
			this.Controls.Add(this.CBDataName);
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "MainWin";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "BootMenu";
			this.Load += new System.EventHandler(this.MainWin_Load);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.ComboBox CBDataName;
		private System.Windows.Forms.Button OKButton;
		private System.Windows.Forms.Timer MainTimer;
		private System.Windows.Forms.CheckBox 無きゃ削除;
	}
}

