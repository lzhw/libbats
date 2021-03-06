#include "ast.ih"

unsigned AST::Node::findAllDeep(vector<shared_ptr<AST::Node> > &res, string const &query) const
{
  unsigned cnt = 0;

  for (NodeVector::const_iterator i = d_nodes.begin();
       i != d_nodes.end(); ++i) {
    cnt += (*i)->findAllDeep(res,query);

    if ((*i)->match(query))
      res.push_back(*i);
    ++cnt;
  }

  return cnt;
}
