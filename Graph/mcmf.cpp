/*
    int n = 5 ;
    MCMF mcmf(n) ;
    
    // add_edge(from, to, capacity, cost)
    mcmf.add_edge(0, 1, 10, 2) ;   // ضلع بسعة 10 وتكلفة 2
    mcmf.add_edge(1, 2, 5, 3) ;    // ضلع بسعة 5 وتكلفة 3
    mcmf.add_edge(0, 2, 8, 7) ;    // ضلع بسعة 8 وتكلفة 7

    int source = 0, sink = 2 ;
    auto [max_flow, min_cost] = mcmf.solve(source, sink) ;

    cout << "Max Flow: " << max_flow << el ;
    cout << "Min Cost: " << min_cost << el ;

    // print edges flow
    for (auto &e : mcmf.get_edges()) {
        cout << e.from << " -> " << e.to << " | Flow: " << e.flow << "/" << e.cap << " | Cost: " << e.cost << el ;
    }
*/

// 0-based
// Directed
struct Edge 
{
    int to ;
    int rev ;
    ll cap ;
    ll flow ;
    ll cost ;
};

struct EdgeInfo 
{
    int from ;
    int to ;
    ll cap ;
    ll flow ;
    ll cost ;
};

struct Path 
{
    vector < int > nodes ; // العقد المكونة للمسار من المصدر إلى الهدف
    ll flow ;              // كمية التدفق المارة في هذا المسار
    ll cost ;              // تكلفة المسار لكل وحدة تدفق واحدة
};

class MCMF 
{
private:
    int n ;
    vector < vector < Edge > > adj ;
    vector < ll > dist ;
    vector < int > parent_node ;
    vector < int > parent_edge ;
    vector < bool > in_queue ;
    vector < pair < int , int > > pos ;
    const ll INF = 1e18 ;

    bool spfa ( int s , int t ) 
    {
        fill(dist.begin() , dist.end() , INF) ;
        fill(in_queue.begin() , in_queue.end() , false) ;
        queue < int > q ;

        dist[s] = 0 ;
        q.push(s) ;
        in_queue[s] = true ;

        while (!q.empty())
        {
            int u = q.front() ;
            q.pop() ;
            in_queue[u] = false ;

            for ( int i = 0 ; i < (int)adj[u].size() ; i ++) 
            {
                const Edge &e = adj[u][i] ;
                if ( e.cap - e.flow > 0 && dist[e.to] > dist[u] + e.cost ) 
                {
                    dist[e.to] = dist[u] + e.cost ;
                    parent_node[e.to] = u ;
                    parent_edge[e.to] = i ;
                    if (!in_queue[e.to]) 
                    {
                        q.push(e.to) ;
                        in_queue[e.to] = true ;
                    }
                }
            }
        }
        return dist[t] != INF ;
    }

public:
    MCMF(int n) : n(n) , adj(n) , dist(n) , parent_node(n) , parent_edge(n) , in_queue(n) {}

    // إضافة ضلع موجه من u إلى v مع سعة (cap) وتكلفة (cost)
    void add_edge(int u , int v , ll cap , ll cost) {

        pos.push_back({u , (int)adj[u].size()}) ;
        Edge a = {v , (int)adj[v].size() , cap , 0 , cost} ;
        Edge b = {u , (int)adj[u].size() , 0 , 0 , -cost} ;
        adj[u].push_back(a) ;
        adj[v].push_back(b) ;
    }

    // ترجع قائمة بالأضلاع الأساسية التي تم إضافتها فقط مع تفاصيل الـ flow
    vector < EdgeInfo > get_edges()
    {
        vector < EdgeInfo > edges ;
        for ( auto &[u , idx] : pos ) 
        {
            const Edge &e = adj[u][idx] ;
            edges.push_back({u , e.to , e.cap , e.flow , e.cost}) ;
        }
        return edges ;
    }

    // ترجع pair يمثل {max_flow , min_cost}
    pair < ll , ll > solve(int s , int t , ll max_flow_limit = 1e18) 
    {
        ll flow = 0 ;
        ll cost = 0 ;

        while (flow < max_flow_limit && spfa(s , t)) 
        {
            ll push = max_flow_limit - flow ;
            int cur = t ;
            while (cur != s) 
            {
                int p = parent_node[cur] ;
                int idx = parent_edge[cur] ;
                push = min(push , adj[p][idx].cap - adj[p][idx].flow) ;
                cur = p ;
            }

            flow += push ;
            cost += push * dist[t] ;

            cur = t ;
            while (cur != s) 
            {
                int p = parent_node[cur] ;
                int idx = parent_edge[cur] ;
                adj[p][idx].flow += push ;
                int rev_idx = adj[p][idx].rev ;
                adj[cur][rev_idx].flow -= push ;
                cur = p ;
            }
        }

        return {flow , cost} ;
    }

    // ترجع المسارات الفعلية التي يمر فيها التدفق من s إلى t
    vector < Path > get_paths(int s , int t) 
    {
        // نسخة مؤقتة من التدفقات الموجبة للأسهم الأصلية فقط
        vector < vector < ll > > cur_flow(n) ;
        for ( int u = 0 ; u < n ; u ++ ) 
        {
            cur_flow[u].resize(adj[u].size() , 0) ;
            for ( int i = 0 ; i < (int)adj[u].size() ; i ++ ) 
            {
                if ( adj[u][i].flow > 0 ) 
                {
                    cur_flow[u][i] = adj[u][i].flow ;
                }
            }
        }

        vector < Path > paths ;

        while ( true ) 
        {
            vector < int > parent_node_path(n , -1) ;
            vector < int > parent_edge_path(n , -1) ;
            vector < bool > vis(n , false) ;
            queue < int > q ;

            q.push(s) ;
            vis[s] = true ;

            while ( !q.empty() ) 
            {
                int u = q.front() ;
                q.pop() ;

                if ( u == t ) break ;

                for ( int i = 0 ; i < (int)adj[u].size() ; i ++ ) 
                {
                    const Edge &e = adj[u][i] ;
                    if ( cur_flow[u][i] > 0 && !vis[e.to] ) 
                    {
                        vis[e.to] = true ;
                        parent_node_path[e.to] = u ;
                        parent_edge_path[e.to] = i ;
                        q.push(e.to) ;
                    }
                }
            }

            // إذا لم يعد هناك مسار يحمل تدفقاً من s إلى t ننهي البحث
            if ( !vis[t] ) break ;

            // حساب التدفق الأدنى المار على هذا المسار
            ll path_flow = INF ;
            int cur = t ;
            while ( cur != s ) 
            {
                int p = parent_node_path[cur] ;
                int idx = parent_edge_path[cur] ;
                path_flow = min(path_flow , cur_flow[p][idx]) ;
                cur = p ;
            }

            // اقتطاع التدفق وبناء المسار
            vector < int > node_path ;
            ll path_cost = 0 ;
            cur = t ;
            while ( cur != s ) 
            {
                node_path.push_back(cur) ;
                int p = parent_node_path[cur] ;
                int idx = parent_edge_path[cur] ;
                cur_flow[p][idx] -= path_flow ;
                path_cost += adj[p][idx].cost ;
                cur = p ;
            }
            node_path.push_back(s) ;
            reverse(node_path.begin() , node_path.end()) ;

            paths.push_back({node_path , path_flow , path_cost}) ;
        }

        return paths ;
    }
};