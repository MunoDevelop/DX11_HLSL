#pragma once
#include "AdapterReader.h"

//static member ??
std::vector<AdapterData> AdapterReader::adapters;

std::vector<AdapterData> AdapterReader::GetAdapterData()
{
	if (adapters.size() > 0) {
		return adapters;
	}
	Microsoft::WRL::ComPtr <IDXGIFactory> pFactory;

	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory),reinterpret_cast<void**>(pFactory.GetAddressOf()));
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create DXGIFactory");
		exit(-1);
	}

	IDXGIAdapter* pAdapter;
	UINT index = 0;
	while (SUCCEEDED(pFactory->EnumAdapters(index, &pAdapter)))
	{
		adapters.push_back(AdapterData(pAdapter));
		index += 1;
	}
	return adapters;
}
AdapterData::AdapterData(IDXGIAdapter* pAdapter) {
	this->pAdapter = pAdapter;
}