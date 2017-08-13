namespace Editor
{
	partial class SelectWin
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
			this.CB選択項目 = new System.Windows.Forms.ComboBox();
			this.OKBtn = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// CB選択項目
			// 
			this.CB選択項目.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.CB選択項目.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.CB選択項目.FormattingEnabled = true;
			this.CB選択項目.Location = new System.Drawing.Point(12, 12);
			this.CB選択項目.Name = "CB選択項目";
			this.CB選択項目.Size = new System.Drawing.Size(245, 20);
			this.CB選択項目.TabIndex = 0;
			// 
			// OKBtn
			// 
			this.OKBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.OKBtn.Location = new System.Drawing.Point(180, 38);
			this.OKBtn.Name = "OKBtn";
			this.OKBtn.Size = new System.Drawing.Size(77, 33);
			this.OKBtn.TabIndex = 1;
			this.OKBtn.Text = "閉じる";
			this.OKBtn.UseVisualStyleBackColor = true;
			this.OKBtn.Click += new System.EventHandler(this.OKBtn_Click);
			// 
			// SelectWin
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(269, 82);
			this.Controls.Add(this.OKBtn);
			this.Controls.Add(this.CB選択項目);
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "SelectWin";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "----";
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.ComboBox CB選択項目;
		private System.Windows.Forms.Button OKBtn;
	}
}
