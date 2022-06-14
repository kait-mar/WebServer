#ifndef __COMPONENT_HPP__
#define __COMPONENT_HPP__

#include <string>
#include <vector>
#include <map>

#include "../Parser/Tokenizer/Tokenizer.hpp"
#include "utils.hpp"

class Component {
	protected:
		bool 			_sin;
		std::string		_dir;
		unsigned		_subs;
		std::multimap <std::string, Component *> _subComp;
	public:
		Component (const std::string &, bool sin = true, unsigned int = 0);
		Component (const Component &);
		Component& operator = (const Component&);
		virtual ~Component ();
		
		virtual Component *clone () const = 0;
		virtual bool isSet () const;
		virtual void pretty_print (std::string tabulation = "") const = 0;
		virtual void syntax_parse (Tokenizer &) = 0;
		bool sin () const { return _sin; }
		bool isSub (const std::string&) const;
		void addSubComponent (Component *);
		const std::string& dir () const { return _dir; } 
		
		template<typename SUB>
		SUB *getSimpleAttribute_ () const {
			SUB *sub;
			for (std::multimap <std::string, Component*>::const_iterator it = _subComp.begin (); it != _subComp.end (); ++it) {
				sub = dynamic_cast <SUB *> (it->second);
				if (sub) return sub;
			}
			return 0x0;
		}
		template<typename SUB>
		std::vector<SUB *> getSubComponents_ () const {
			std::vector <SUB *> _subs;
			SUB *sub;
			for (std::multimap <std::string, Component*>::const_iterator it = _subComp.begin (); it != _subComp.end (); ++it) {
				sub = dynamic_cast<SUB *> (it->second);
				if (sub)
					_subs.push_back (sub);
			}
			return _subs;
		}
};

#endif