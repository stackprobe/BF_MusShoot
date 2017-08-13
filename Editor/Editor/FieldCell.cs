using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Editor
{
	public class FieldCell
	{
		public FieldCellData BackCD;
		public FieldCellData FrontCD;

		public FieldCell(FieldCellData backCD, FieldCellData frontCD)
		{
			this.BackCD = backCD;
			this.FrontCD = frontCD;
		}

		public FieldCell GetClone()
		{
			return new FieldCell(
				this.BackCD == null ? null : this.BackCD.GetClone(),
				this.FrontCD == null ? null : this.FrontCD.GetClone()
				);
		}
	}
}
