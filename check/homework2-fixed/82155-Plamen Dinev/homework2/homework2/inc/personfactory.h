/*
 * personfactory.h
 *
 *  Created on: 23.05.2021 Рі.
 *      Author: plamen
 */

#ifndef SRC_PERSONFACTORY_H_
#define SRC_PERSONFACTORY_H_

#include "person.h"

#include <unordered_set>

class person_factory
{

	//singleton stuff
public:

	static person_factory& get_instance();

private:
	person_factory() = default;
	~person_factory();

public:

	person_factory(const person_factory&) = delete;
	person_factory(person_factory&&) = delete;
	void operator=(const person_factory&)  = delete;
	void operator=(person_factory&&) = delete;

	//real implementation

private:

	// we store Person(s) in heap, because unordered_set
	// iterrator invalidation might mess the addresses
	// if Person(s) were stored in the unordered_set directly
	std::unordered_set<Person*,
					   Person::hash_id_only,
					   Person::cmp_equal_id_only
					   > all_people;

public:

	inline const std::unordered_set<Person*,
	   Person::hash_id_only,
	   Person::cmp_equal_id_only
	   >& get_all() const noexcept
	{ return this->all_people; }

	Person* create_person(unsigned int id, std::string name);

	Person* get(unsigned int id) const;
	void remove(Person* p);
	void remove(unsigned int id);
};

#endif /* SRC_PERSONFACTORY_H_ */
