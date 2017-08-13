namespace Editor
{
	partial class EditWin
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
			this.MainSplit = new System.Windows.Forms.SplitContainer();
			this.LSplit = new System.Windows.Forms.SplitContainer();
			this.EnemyPicBox = new System.Windows.Forms.PictureBox();
			this.LBPanel = new System.Windows.Forms.Panel();
			this.RSplit = new System.Windows.Forms.SplitContainer();
			this.CPVSheet = new System.Windows.Forms.DataGridView();
			this.PVSheet = new System.Windows.Forms.DataGridView();
			this.MainSplit.Panel1.SuspendLayout();
			this.MainSplit.Panel2.SuspendLayout();
			this.MainSplit.SuspendLayout();
			this.LSplit.Panel1.SuspendLayout();
			this.LSplit.Panel2.SuspendLayout();
			this.LSplit.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.EnemyPicBox)).BeginInit();
			this.RSplit.Panel1.SuspendLayout();
			this.RSplit.Panel2.SuspendLayout();
			this.RSplit.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.CPVSheet)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.PVSheet)).BeginInit();
			this.SuspendLayout();
			// 
			// MainSplit
			// 
			this.MainSplit.Dock = System.Windows.Forms.DockStyle.Fill;
			this.MainSplit.Location = new System.Drawing.Point(0, 0);
			this.MainSplit.Name = "MainSplit";
			// 
			// MainSplit.Panel1
			// 
			this.MainSplit.Panel1.Controls.Add(this.LSplit);
			// 
			// MainSplit.Panel2
			// 
			this.MainSplit.Panel2.Controls.Add(this.RSplit);
			this.MainSplit.Size = new System.Drawing.Size(502, 448);
			this.MainSplit.SplitterDistance = 84;
			this.MainSplit.TabIndex = 0;
			// 
			// LSplit
			// 
			this.LSplit.Dock = System.Windows.Forms.DockStyle.Fill;
			this.LSplit.Location = new System.Drawing.Point(0, 0);
			this.LSplit.Name = "LSplit";
			this.LSplit.Orientation = System.Windows.Forms.Orientation.Horizontal;
			// 
			// LSplit.Panel1
			// 
			this.LSplit.Panel1.Controls.Add(this.EnemyPicBox);
			// 
			// LSplit.Panel2
			// 
			this.LSplit.Panel2.Controls.Add(this.LBPanel);
			this.LSplit.Size = new System.Drawing.Size(84, 448);
			this.LSplit.SplitterDistance = 203;
			this.LSplit.TabIndex = 0;
			this.LSplit.SplitterMoved += new System.Windows.Forms.SplitterEventHandler(this.LSplit_SplitterMoved);
			// 
			// EnemyPicBox
			// 
			this.EnemyPicBox.BackColor = System.Drawing.SystemColors.Control;
			this.EnemyPicBox.Dock = System.Windows.Forms.DockStyle.Fill;
			this.EnemyPicBox.Location = new System.Drawing.Point(0, 0);
			this.EnemyPicBox.Name = "EnemyPicBox";
			this.EnemyPicBox.Size = new System.Drawing.Size(84, 203);
			this.EnemyPicBox.TabIndex = 0;
			this.EnemyPicBox.TabStop = false;
			this.EnemyPicBox.Click += new System.EventHandler(this.EnemyPicBox_Click);
			// 
			// LBPanel
			// 
			this.LBPanel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.LBPanel.Location = new System.Drawing.Point(0, 0);
			this.LBPanel.Name = "LBPanel";
			this.LBPanel.Size = new System.Drawing.Size(84, 241);
			this.LBPanel.TabIndex = 0;
			this.LBPanel.Click += new System.EventHandler(this.LBPanel_Click);
			// 
			// RSplit
			// 
			this.RSplit.Dock = System.Windows.Forms.DockStyle.Fill;
			this.RSplit.Location = new System.Drawing.Point(0, 0);
			this.RSplit.Name = "RSplit";
			this.RSplit.Orientation = System.Windows.Forms.Orientation.Horizontal;
			// 
			// RSplit.Panel1
			// 
			this.RSplit.Panel1.Controls.Add(this.CPVSheet);
			// 
			// RSplit.Panel2
			// 
			this.RSplit.Panel2.Controls.Add(this.PVSheet);
			this.RSplit.Size = new System.Drawing.Size(414, 448);
			this.RSplit.SplitterDistance = 217;
			this.RSplit.TabIndex = 0;
			this.RSplit.SplitterMoved += new System.Windows.Forms.SplitterEventHandler(this.RSplit_SplitterMoved);
			// 
			// CPVSheet
			// 
			this.CPVSheet.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.CPVSheet.Dock = System.Windows.Forms.DockStyle.Fill;
			this.CPVSheet.Location = new System.Drawing.Point(0, 0);
			this.CPVSheet.Name = "CPVSheet";
			this.CPVSheet.RowTemplate.Height = 21;
			this.CPVSheet.Size = new System.Drawing.Size(414, 217);
			this.CPVSheet.TabIndex = 0;
			this.CPVSheet.CellDoubleClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.CPVSheet_CellDoubleClick);
			this.CPVSheet.KeyDown += new System.Windows.Forms.KeyEventHandler(this.CPVSheet_KeyDown);
			// 
			// PVSheet
			// 
			this.PVSheet.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.PVSheet.Dock = System.Windows.Forms.DockStyle.Fill;
			this.PVSheet.Location = new System.Drawing.Point(0, 0);
			this.PVSheet.Name = "PVSheet";
			this.PVSheet.RowTemplate.Height = 21;
			this.PVSheet.Size = new System.Drawing.Size(414, 227);
			this.PVSheet.TabIndex = 0;
			this.PVSheet.CellDoubleClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.PVSheet_CellDoubleClick);
			this.PVSheet.KeyDown += new System.Windows.Forms.KeyEventHandler(this.PVSheet_KeyDown);
			// 
			// EditWin
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(502, 448);
			this.Controls.Add(this.MainSplit);
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "EditWin";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "EditWin";
			this.Activated += new System.EventHandler(this.EditWin_Activated);
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.EditWin_FormClosed);
			this.MainSplit.Panel1.ResumeLayout(false);
			this.MainSplit.Panel2.ResumeLayout(false);
			this.MainSplit.ResumeLayout(false);
			this.LSplit.Panel1.ResumeLayout(false);
			this.LSplit.Panel2.ResumeLayout(false);
			this.LSplit.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.EnemyPicBox)).EndInit();
			this.RSplit.Panel1.ResumeLayout(false);
			this.RSplit.Panel2.ResumeLayout(false);
			this.RSplit.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.CPVSheet)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.PVSheet)).EndInit();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.SplitContainer MainSplit;
		private System.Windows.Forms.SplitContainer RSplit;
		private System.Windows.Forms.SplitContainer LSplit;
		private System.Windows.Forms.PictureBox EnemyPicBox;
		private System.Windows.Forms.DataGridView CPVSheet;
		private System.Windows.Forms.DataGridView PVSheet;
		private System.Windows.Forms.Panel LBPanel;

	}
}
