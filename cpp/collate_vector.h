template <typename T>
std::shared_ptr<std::vector<T>> CollateVector(const std::shared_ptr<std::vector<T>>& vec1,
	const std::shared_ptr<std::vector<T>>& vec2)
{
	auto data = std::make_shared<std::vector<T>>();
	data->reserve(vec1->size() + vec2->size());
	data->insert(data->end(), vec1->begin(), vec1->end());
	data->insert(data->end(), vec2->begin(), vec2->end());
	return data;
