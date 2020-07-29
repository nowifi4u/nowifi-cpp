#pragma once

#include <memory>
#include <string>

using BYTE = unsigned char;

template <class Ty>
class RawBin {

public:

	RawBin() = delete;
	RawBin(const RawBin&) = delete;

	static void arr_to_byte(BYTE* dst, const Ty* data, const size_t size) {
		memcpy(dst, data, sizeof data * size);
	}

	static std::unique_ptr<BYTE> arr_to_byte(const Ty* data, const size_t size) {
		BYTE* result = new BYTE[size];
		arr_to_byte(result, data, size);
		return std::make_unique<BYTE>(result);
	}

	static std::string arr_to_string(const Ty* data, const size_t size) {
		return std::string(RawBin::arr_to_byte(data, size).get(), sizeof data[0] * size);
	}

	static void to_byte(BYTE* dst, const Ty& data) {
		arr_to_byte(dst, &data, 1);
	}

	static std::unique_ptr<BYTE> to_byte(const Ty& data) {
		return arr_to_byte(&data, 1);
	}

	static std::string to_string(const Ty& data) {
		return arr_to_string(&data, 1);
	}



	static void arr_from_byte(Ty* dst, const BYTE* bytes, const size_t size) {
		memcpy(dst, bytes, size * sizeof size);
	}

	static std::unique_ptr<Ty> arr_from_byte(const BYTE* bytes, const size_t size) {
		Ty* result = new Ty[size];
		arr_from_byte(result, bytes, size);
		return std::make_unique<Ty>(result);
	}

	static void arr_from_string(Ty* dst, const std::string& bytes, const size_t size) {
		arr_from_byte(dst, bytes.c_str(), size);
	}

	static void from_byte(Ty& dst, const BYTE* bytes) {
		arr_from_byte(&dst, bytes, 1);
	}

	static void from_string(Ty& dst, const std::string& bytes) {
		from_byte(dst, bytes.c_str());
	}
};