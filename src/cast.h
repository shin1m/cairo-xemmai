	template<typename T0>
	struct t_cast
	{
		template<typename T1>
		static T0* f_call(T1&& a_object)
		{
			auto p = static_cast<T0*>(f_object(std::forward<T1>(a_object))->f_pointer());
			if (!p->f_valid()) t_throwable::f_throw(L"accessing from other thread.");
			if (!*p) t_throwable::f_throw(L"already destroyed.");
			return p;
		}
	};
	template<typename T0>
	struct t_as
	{
		template<typename T1>
		static T0 f_call(T1&& a_object)
		{
			return *t_cast<typename t_fundamental<T0>::t_type>::f_call(std::forward<T1>(a_object));
		}
	};
	template<typename T0>
	struct t_as<T0*>
	{
		template<typename T1>
		static T0* f_call(T1&& a_object)
		{
			return reinterpret_cast<size_t>(f_object(std::forward<T1>(a_object))) == t_value::e_tag__NULL ? nullptr : t_cast<T0>::f_call(std::forward<T1>(a_object));
		}
	};
	template<typename T0>
	struct t_is
	{
		template<typename T1>
		static bool f_call(T1&& a_object)
		{
			auto p = f_object(std::forward<T1>(a_object));
			return reinterpret_cast<size_t>(p) >= t_value::e_tag__OBJECT && dynamic_cast<t_type_of<typename t_fundamental<T0>::t_type>*>(f_as<t_type*>(p->f_type())) != nullptr;
		}
	};
	template<typename T0>
	struct t_is<T0*>
	{
		template<typename T1>
		static bool f_call(T1&& a_object)
		{
			auto p = f_object(std::forward<T1>(a_object));
			switch (reinterpret_cast<size_t>(p)) {
			case t_value::e_tag__NULL:
				return true;
			case t_value::e_tag__BOOLEAN:
			case t_value::e_tag__INTEGER:
			case t_value::e_tag__FLOAT:
				return false;
			default:
				return dynamic_cast<t_type_of<typename t_fundamental<T0>::t_type>*>(f_as<t_type*>(p->f_type())) != nullptr;
			}
		}
	};

	template<typename T_extension, typename T>
	static t_scoped f_transfer(T_extension* a_extension, T&& a_value)
	{
		return a_value->f_object();
	}
