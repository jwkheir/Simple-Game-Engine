#pragma once


namespace Merlin{
	// Exercise 2.1
	class Object{
	private:
		static int instances;
		int id;
	public:
		Object();
		~Object();
		int GetID(){ return id; }
		bool operator ==(const Object& rhdObj){
			return (this->id == rhdObj.id);
		}
		bool operator !=(const Object& rhdObj){
			return (this->id != rhdObj.id);
		}
	};
}

