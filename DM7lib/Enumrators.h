#pragma once

namespace MifuminLib {
	namespace DM7Lib {

		public enum class Reset { GM, GS, XG };

		public enum class SegmentFlags : DWORD {
			None             = 0,
			Reftime          = 64,
			Secondary        = 128,
			Queue            = 256,
			Control          = 512,
			AfterPrepareTime = 1<<10,
			Grid             = 1<<11,
			Beat             = 1<<12,
			Measure          = 1<<13,
			Default          = 1<<14,
			NoInvalidate     = 1<<15,
		};

	}
}