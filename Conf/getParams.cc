#include "conf.ih"

XMLNodeSet Conf::getParams(std::string const& behaviorTree, std::string const &behaviorid, std::string const &path)
{
  //_debugLevel1(name);
  std::ostringstream xpath("");
  xpath << "/conf/behavior-tree[@id='" << behaviorTree << "']/behaviors/behavior[@id='" << behaviorid << "']/param" << path;
  _debugLevel1(xpath.str());
  return selectXPath(xpath.str());
}
