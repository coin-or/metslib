// -*- C++ -*-
//
// METS lib source file - observer.h
//
// Copyright (C) 2006-2008 Mirko Maischberger <mirko.maischberger@gmail.com>
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef METS_OBSERVER_H_
#define METS_OBSERVER_H_

#include <set>
#include <algorithm> 

namespace mets {

  using namespace std;
  
  template<typename observed_subject>
    class observer; // forward declaration

  template<typename observed_subject>
    class subject; // forward declaration

  ///
  /// @brief Functor class to update observers with a for_each,
  ///        only intended for internal use.
  ///
  template<typename observed_subject>
    class update_observer 
    {
    public:
      /// @brief Ctor.
      update_observer(observed_subject* who) : who_m(who) {}
      /// @brief Subscript operator to update an observer.
      void 
      operator()(observer<observed_subject>* o) { o->update(who_m); }
    private:
      update_observer();
      observed_subject* who_m;
    };

  ///
  /// @brief template class for subjects (cfr. Observer Design Pattern).
  ///
  /// You must declare the subject of the observations with:
  ///
  ///   class my_observed_sbj : public subject<my_observed_sbj>
  ///
  /// Than you should call notify() manually or automatically 
  /// from every method that changes the subject status.
  ///
  ///  Only attached observers (cfr. attach() and detach() methods)
  ///  will be notified.
  ///
  template<typename observed_subject>
    class subject
    {
    public:
      virtual
      ~subject() {};
      /// @brief Attach a new observer to this subject.
      ///
      /// @param o: a new observer for this subject.
      ///           if the observer was already present 
      ///           nothing happens.
      virtual void
      attach(observer<observed_subject>& o);
      /// @brief Detach a new observer to this subject.
      ///
      /// @param o: observer to detach from this subject.
      ///           if the observer "o" was not present
      ///           nothing happens.
      virtual void
      detach(observer<observed_subject>& o);
      /// @brief Notify all attached observers.
      ///
      /// When this method is called every 
      /// observed_subject#update method is called
      /// and "this" subject is passed as a param.
      /// 
      virtual void
      notify();
    protected:
      subject();
      set<observer<observed_subject>*> observers_m;
    };

  ///
  /// @brief Template base class for the observers of some observed_subject
  /// 
  /// You should declare a new observer type of some my_subject this way:
  ///
  ///   class my_observer : public observer<my_subject>
  ///
  /// Every time notify() is called on the subject every attached
  /// observer is updated.
  ///
  template<typename observed_subject>
    class observer 
    {
    public:
      virtual
      ~observer() {};
      /// @brief This method is automatically called when this
      ///        observer is attached to a "notified" subject.
      ///
      /// @param subject: The subject that was notified and that
      ///                 called our update method.
      virtual void
      update(observed_subject*) = 0;
    protected:
      observer() {};
    };


  // Implementation of the template methods in STL

  template<typename observed_subject>
    subject<observed_subject>::subject() 
      : observers_m() { }
  
  template<typename observed_subject>
    void 
    subject<observed_subject>::attach(observer<observed_subject>& o)
    { observers_m.insert(&o); }
  
  template<typename observed_subject>
    void
    subject<observed_subject>::detach(observer<observed_subject>& o)
    { observers_m.erase(&o); }
  
  template<typename observed_subject>
    void
    subject<observed_subject>::notify() 
    {
      // dynamic cast to safely pass the real underlying subject 
      // type to the observers.
      observed_subject* real_subject = dynamic_cast<observed_subject*>(this);
      for_each(observers_m.begin(), observers_m.end(), 
	       update_observer<observed_subject>(real_subject));
    }
  
}

#endif // METS_OBSERVER_H_
