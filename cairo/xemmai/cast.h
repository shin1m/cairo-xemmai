	template<typename T0, typename T1>
	struct t_cast
	{
		static T0* f_call(T1 a_object)
		{
			T0* p = static_cast<T0*>(f_object(a_object)->f_pointer());
			if (!p->f_valid()) t_throwable::f_throw(L"accessing from other thread.");
			if (!*p) t_throwable::f_throw(L"already destroyed.");
			return p;
		}
	};
	template<typename T0, typename T1>
	struct t_as
	{
		typedef T0 t_type;

		static T0 f_call(T1 a_object)
		{
			return *t_cast<T0, T1>::f_call(a_object);
		}
	};
	template<typename T0, typename T1>
	struct t_as<T0*, T1>
	{
		typedef T0* t_type;

		static T0* f_call(T1 a_object)
		{
			return reinterpret_cast<size_t>(f_object(a_object)) == t_value::e_tag__NULL ? 0 : t_cast<T0, T1>::f_call(a_object);
		}
	};
	template<typename T0, typename T1>
	struct t_as<T0&, T1>
	{
		typedef T0& t_type;

		static T0& f_call(T1 a_object)
		{
			return *t_cast<T0, T1>::f_call(a_object);
		}
	};
	template<typename T0, typename T1>
	struct t_is
	{
		static bool f_call(T1 a_object)
		{
			using namespace ::xemmai;
			return reinterpret_cast<size_t>(f_object(a_object)) >= t_value::e_tag__OBJECT && dynamic_cast<t_type_of<typename t_fundamental<T0>::t_type>*>(f_as<t_type*>(f_object(a_object)->f_type())) != 0;
		}
	};
	template<typename T0, typename T1>
	struct t_is<T0*, T1>
	{
		static bool f_call(T1 a_object)
		{
			using namespace ::xemmai;
			switch (reinterpret_cast<size_t>(f_object(a_object))) {
			case t_value::e_tag__NULL:
				return true;
			case t_value::e_tag__BOOLEAN:
			case t_value::e_tag__INTEGER:
			case t_value::e_tag__FLOAT:
				return false;
			default:
				return dynamic_cast<t_type_of<typename t_fundamental<T0>::t_type>*>(f_as<t_type*>(f_object(a_object)->f_type())) != 0;
			}
		}
	};

	template<typename T_extension, typename T>
	static t_transfer f_transfer(T_extension* a_extension, T a_value)
	{
		return a_value->f_object();
	}
