/**
 * Shadow Daemon -- Web Application Firewall
 *
 *   Copyright (C) 2014-2015 Hendrik Buchwald <hb@zecure.org>
 *
 * This file is part of Shadow Daemon. Shadow Daemon is free software: you can
 * redistribute it and/or modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation, version 2.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 */

#include "request.h"

void swd::request::set_profile(swd::profile_ptr profile) {
	profile_ = profile;
}

swd::profile_ptr swd::request::get_profile() {
	return profile_;
}

void swd::request::add_parameter(std::string path, std::string value) {
	swd::parameter_ptr parameter(new swd::parameter(path, value));
	parameters_[path] = parameter;
}

swd::parameters& swd::request::get_parameters() {
	return parameters_;
}

void swd::request::append_content(char input) {
	content_.push_back(input);
}

std::string swd::request::get_content() {
	return content_;
}

void swd::request::append_signature(char input) {
	signature_.push_back(input);
}

std::string swd::request::get_signature() {
	return signature_;
}

void swd::request::append_profile_id(char input) {
	profile_id_.push_back(input);
}

int swd::request::get_profile_id() {
	return atoi(profile_id_.c_str());
}

void swd::request::set_client_ip(std::string client_ip) {
	client_ip_ = client_ip;
}

std::string swd::request::get_client_ip() {
	return client_ip_;
}

void swd::request::set_caller(std::string caller) {
	caller_ = caller;
}

std::string swd::request::get_caller() {
	return caller_;
}

void swd::request::set_resource(std::string resource) {
	resource_ = resource;
}

std::string swd::request::get_resource() {
	return resource_;
}

void swd::request::add_integrity_rule(swd::integrity_rule_ptr rule) {
	integrity_rules_.push_back(rule);
}

const swd::integrity_rules& swd::request::get_integrity_rules() {
	return integrity_rules_;
}

void swd::request::set_total_integrity_rules(int total_integrity_rules) {
	total_integrity_rules_ = total_integrity_rules;
}

int swd::request::get_total_integrity_rules() {
	return total_integrity_rules_;
}

void swd::request::add_hash(std::string algorithm, std::string digest) {
	swd::hash_ptr hash(new swd::hash(algorithm, digest));
	hashes_[algorithm] = hash;
}

swd::hashes& swd::request::get_hashes() {
	return hashes_;
}

swd::hash_ptr swd::request::get_hash(std::string algorithm) {
	return hashes_[algorithm];
}

void swd::request::is_threat(bool threat) {
	threat_ = threat;
}

bool swd::request::is_threat() {
	return threat_;
}

bool swd::request::has_threats() {
	/* Iterate over all parameters and check for threats. */
	for (swd::parameters::iterator it_parameter = parameters_.begin();
	 it_parameter != parameters_.end(); it_parameter++) {
		swd::parameter_ptr parameter((*it_parameter).second);

		/* We only need to know if there is at least one threat. */
		if (parameter->is_threat()) {
			return true;
		}
	}

	return false;
}
