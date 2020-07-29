#pragma once

#include <iostream>

namespace nw {

	template<class Ty, char sep>
	struct InputSepatator {
		Ty value;
		operator Ty& () const { return value; }
	};

	template<class Ty, char sep>
	std::istream& operator>>(std::istream& in, InputSepatator<Ty, sep>& separator)
	{
		if (!(in >> separator.value))
			return in;
		if (in.peek() == sep)
			in.ignore();
		//else
		//	in.clear();
		return in;
	}

} // namespace nw