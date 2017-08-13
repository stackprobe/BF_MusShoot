using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Editor
{
	public class ResourceData
	{
		/// <summary>
		/// 未定義値は行自体存在しないが、定義の前の未定義ならば何か行が無ければならない。
		/// その代替として DEFAULT_VALUE を使用する。
		/// 
		/// 1行目: 123
		/// 2行目: 未定義
		/// この場合
		/// 1行目: 123
		/// となる。
		/// 
		/// 1行目: 未定義
		/// 2行目: 456
		/// この場合
		/// 1行目: *
		/// 2行目: 456
		/// となる。
		/// </summary>
		public const string DEFAULT_VALUE = "*";

		private string[] Lines;
		private int ReadIndex;

		public ResourceData(string file)
		{
			try
			{
				this.Lines = File.ReadAllLines(file, Tools.CP932);
			}
			catch
			{ }

			if (this.Lines == null)
				this.Lines = new string[] { };

			if (this.Lines.Length == 0)
				this.Lines = new string[] { DEFAULT_VALUE };
		}

		public bool HasValue()
		{
			return this.ReadIndex < this.Lines.Length;
		}
		public string ReadValue_DIRECT(string substituteValue)
		{
			string value;

			if (this.ReadIndex < this.Lines.Length)
			{
				value = this.Lines[this.ReadIndex];
				this.ReadIndex++;
			}
			else
				value = null;

			if (value == null || value == "")
				value = substituteValue;

			return value;
		}
		public string ReadValue()
		{
			return this.ReadValue_DIRECT(DEFAULT_VALUE);
		}
		public ResourceDataList ReadBlock()
		{
			List<string> result = new List<string>();

			for (; ; )
			{
				string value = this.ReadValue_DIRECT(null);

				if (value == null)
					break;

				result.Add(value);
			}
			return new ResourceDataList(result);
		}
	}
	public class ResourceDataList
	{
		private List<string> ValueList;

		public ResourceDataList(List<string> valueList)
		{
			if (valueList == null)
				valueList = new List<string>();

			this.ValueList = valueList;
		}
		public ResourceDataList()
			: this(null)
		{ }

		public string GetValue(int index)
		{
			try
			{
				string value = this.ValueList[index];

				value = value.Trim();

				if (value == "")
					throw new Exception();

				return value;
			}
			catch
			{ }

			return ResourceData.DEFAULT_VALUE;
		}
		public void SetValue(int index, string value)
		{
			if (index < 0)
				return;

			while (this.ValueList.Count <= index)
			{
				this.ValueList.Add(null);
			}
			this.ValueList[index] = value;
		}

		public List<string> GetValueList()
		{
			List<string> result = new List<string>();

			for(int index = 0; index < this.ValueList.Count; index++)
			{
				result.Add(this.GetValue(index));
			}
			while (1 <= result.Count && result[result.Count - 1] == ResourceData.DEFAULT_VALUE) // trim trailer
			{
				result.RemoveAt(result.Count - 1);
			}
			if (result.Count == 0) // anti empty
			{
				result.Add(ResourceData.DEFAULT_VALUE);
			}
			return result;
		}
		public List<string> GetValueList_RTrim()
		{
			List<string> result = this.GetValueList();

			if (result[result.Count - 1] == ResourceData.DEFAULT_VALUE)
				result = new List<string>();

			return result;
		}
		public ResourceDataList GetClone()
		{
			return new ResourceDataList(new List<string>(this.ValueList.ToArray()));
		}
	}
}
