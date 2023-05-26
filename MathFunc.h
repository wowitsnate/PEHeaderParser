#pragma once

template <typename T>
inline bool isInRangeInclusive(T val, T min, T max) {
	return (val >= min && val <= max);
}

template <typename T>
inline bool isInRangeExclusiveUpper(T val, T min, T max) {
	return (val >= min && val < max);
}

template <typename T>
inline bool isInRangeExclusiveLower(T val, T min, T max) {
	return (val > min && val <= max);
}

template <typename T>
inline bool isInRangeExclusive(T val, T min, T max) {
	return (val > min && val < max);
}
